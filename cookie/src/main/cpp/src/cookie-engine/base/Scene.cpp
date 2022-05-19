//
// Created by Antiufieiev Michael on 07.08.2021.
//
#include <Mesh.hpp>
#include <CookieFactory.hpp>
#include "Scene.hpp"
#include "Cookie.hpp"

namespace cookie {

	Scene::Scene() : drawUtils(CookieFactory::provideDrawUtils()),
					 batchManager(std::make_unique<BatchManager>()),
					 globalBufferStorage(CookieFactory::provideGlobalBufferStorage()),
					 sceneSectorManager(CookieFactory::provideSceneSectorManager(1, glm::vec4(1))) {
		auto width = Cookie::getInstance().getPlatformData().width();
		auto height = Cookie::getInstance().getPlatformData().height();
		sceneSettings = std::make_unique<SceneSettings>(
				width, height, 2.0f, 3.0f, 9.0f, 1.0472f, 1.0f, 100.0f
		);
		vMat = glm::lookAt(
				sceneSettings->cameraPos,
				glm::vec3(0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f)
		);
		drawUtils->enableDepthTest();
		drawUtils->cullFace();
	}

	Scene::~Scene() = default;

	void Scene::display(
			const std::chrono::steady_clock::time_point &currentTime,
			const std::chrono::steady_clock::time_point &currentTimeDelta
	) {
		drawUtils->clearBuffers();
		batchManager->draw(*drawUtils);
	}

	void Scene::prepareRendering() {
		globalBufferStorage->updateMatrices(sceneSettings->perspectiveMx, vMat);
		batchManager->syncWithVideoBuffer();
		framerate.invalidateFrameRate();
		globalBufferStorage->bind();
	}

	void Scene::renderFrame() {
		framerate.invalidateFrameRate();
		display(framerate.frameTime, framerate.frameTime);
		drawUtils->swapBuffers();
	}

	SceneSettings &Scene::getSettings() {
		return *sceneSettings;
	}

	void Scene::addObject(const std::shared_ptr<SceneObject> &sceneObject) {
		sceneObjects.push_back(sceneObject);
		batchManager->onNewObject(sceneObject);
	}

	void Scene::removeObject(const std::shared_ptr<SceneObject> &sceneObject) {
		sceneObjects.erase(
				std::find(sceneObjects.begin(), sceneObjects.end(), sceneObject)
		);
	}
}
