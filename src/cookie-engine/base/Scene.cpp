//
// Created by Antiufieiev Michael on 07.08.2021.
//
#include <Mesh.hpp>
#include "Scene.hpp"
#include "Cookie.hpp"

namespace cookie {

	Scene::Scene() : drawUtils(CookieFactory::provideDrawUtils()),
					 batchManager(std::make_unique<BatchManager>()),
					 globalBufferStorage(CookieFactory::provideCrossBatchBufferStorage()){
		auto width = cookie::engine->platformData->width();
		auto height = cookie::engine->platformData->height();
		sceneSettings = std::make_unique<SceneSettings>(
				width, height, 10.0f, 100.0f, 300.0f, 1.0472f, 300.1f, 1000.0f
		);
		vMat = glm::translate(glm::mat4(1.0f), -1.0f * sceneSettings->cameraPos);
		globalBufferStorage->updateMatrices(sceneSettings->perspectiveMx, vMat);
		drawUtils->enableDepthTest();
		drawUtils->cullFace();
	}

	Scene::~Scene() = default;

	void Scene::display(double currentTime, double currentTimeDelta) {
		drawUtils->clearBuffers();
		for(auto& sceneobj:sceneObjects) {
			sceneobj->draw(*drawUtils, vMat,sceneSettings->perspectiveMx);
		}
		batchManager->draw(*drawUtils);
	}

	void Scene::startLoop() {
		batchManager->syncWithVideoBuffer();
		framerate.invalidateFrameRate();
		double last = framerate.frameTime;
		cookie::defaultShader->use();
		globalBufferStorage->bind();
		while (!drawUtils->shouldCloseWindow()) {
			framerate.invalidateFrameRate();
			display(framerate.frameTime, framerate.frameTime - last);
			drawUtils->swapBuffers();
			drawUtils->listenInputEvents();
			last = framerate.frameTime;
		}
	}

	SceneSettings &Scene::getSettings() {
		return *sceneSettings;
	}

	void Scene::addObject(const std::shared_ptr<SceneObject> &sceneObject) {
		sceneObjects.push_back(sceneObject);
		batchManager->onNewObject(sceneObject);
	}
}
