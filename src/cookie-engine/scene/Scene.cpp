//
// Created by Antiufieiev Michael on 07.08.2021.
//
#include <algorithm>
#include "CookieFactory.hpp"
#include "Cube.hpp"
#include "Scene.hpp"
#include "Cookie.hpp"
#include "SceneSettings.hpp"
#include "BatchManager.hpp"
#include "SceneSectorManager.hpp"
#include "GlobalBufferStorage.hpp"
#include "MeshComponent.hpp"

namespace cookie {

	Scene::Scene() : drawUtils(CookieFactory::provideDrawUtils()),
					 batchManager(std::make_unique<BatchManager>()),
					 sceneSectorManager(CookieFactory::provideSceneSectorManager(1, Bounds(glm::vec4(-100, -100, -100, 1), glm::vec4(100, 100, 100, 1)))),
					 sceneSettings(
							 std::make_unique<SceneSettings>(
									 Cookie::getInstance().getPlatformData().width(),
									 Cookie::getInstance().getPlatformData().height(),
									 0.0f, 0.0f, -10.5f, 45.0f, 0.1f, 1000.0f
							 )
					 ),
					 vMat(glm::lookAt(sceneSettings->cameraPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f))) {
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
//		currentShader = CookieFactory::provideShader(
//				R"(D:\Hope\Projects\CookieEngine\assets\shader\vertex\vertex.glsl)",
//				R"(D:\Hope\Projects\CookieEngine\assets\shader\fragment\fragment.glsl)"
//		);
//		currentShader->use();
//		globalBufferStorage->updateMatrices(sceneSettings->perspectiveMx, vMat);
		batchManager->onStart();
	}

	void Scene::renderFrame() {
		framerate.invalidateFrameRate();
		sceneSectorManager->update();
		display(framerate.frameTime, framerate.frameTime);
	}

	void Scene::addObject(const std::shared_ptr<SceneObject> &sceneObject) {
		sceneObjects.push_back(sceneObject);
		batchManager->onNewObject(sceneObject);
		sceneSectorManager->addObject(sceneObject);
	}

	void Scene::removeObject(const std::shared_ptr<SceneObject> &sceneObject) {
		sceneObjects.erase(std::find(sceneObjects.begin(), sceneObjects.end(), sceneObject));
		sceneSectorManager->removeObject(sceneObject);
	}

	SceneSettings &Scene::getSettings() {
		return *sceneSettings;
	}

	void Scene::fillScene() {
		auto model = SceneObject::fromPath(R"(D:\Hope\Projects\CookieEngine\assets\adamHead\adamHead.gltf)");
		addObject(model);
	}

	void Scene::resize(int32_t width, int32_t height) {
		drawUtils->setViewport(width, height);
	}

	bool Scene::isTerminateRequested() {
		return drawUtils->shouldCloseWindow();
	}
}
