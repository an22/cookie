//
// Created by Antiufieiev Michael on 07.08.2021.
//
#include <Mesh.hpp>
#include <CookieFactory.hpp>
#include <Cube.hpp>
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
				width, height, 0.0f, 0.0f, 0.2f, 1.0472f, 0.1f, 1000.0f
		);
		vMat = glm::lookAt(
				sceneSettings->cameraPos,
				glm::vec3(0.0f,0.0f,0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f)
		);
	}

	Scene::~Scene() = default;

	void Scene::display(
			const std::chrono::steady_clock::time_point &currentTime,
			const std::chrono::steady_clock::time_point &currentTimeDelta
	) {
		drawUtils->clearBuffers();
		batchManager->draw(*drawUtils);
		drawUtils->swapBuffers();
	}

	void Scene::prepareRendering() {
		fillScene();
		drawUtils->enableDepthTest();
		drawUtils->cullFace();
		framerate.invalidateFrameRate();
		batchManager->syncWithVideoBuffer();
		globalBufferStorage->updateMatrices(sceneSettings->perspectiveMx, vMat);
		globalBufferStorage->bind();
		currentShader = CookieFactory::provideShader(
				"shader/vertex/vertex.glsl",
				"shader/fragment/fragment.glsl"
		);
	}

	void Scene::renderFrame() {
		framerate.invalidateFrameRate();
		currentShader->use();
		display(framerate.frameTime, framerate.frameTime);
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

	SceneSettings &Scene::getSettings() {
		return *sceneSettings;
	}

	void Scene::fillScene() {
		addObject(std::make_shared<cookie::Cube>(0.0f, 0.0f, 0.0f));
	}

	void Scene::resize(int32_t width, int32_t height) {
		drawUtils->setViewport(width, height);
	}
}
