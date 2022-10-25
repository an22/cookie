//
// Created by Michael on 10/25/2022.
//

#include "Renderer.hpp"
#include "Scene.hpp"
#include "Initializer.hpp"
#include "CookieFactory.hpp"
#include "Cookie.hpp"
#include "PlatformSpecificData.hpp"

namespace cookie {
	Renderer::Renderer(PlatformSpecificData &data) : initializer(CookieFactory::provideInitializer()),
													 currentScene(nullptr) {
		initializer->initGraphicsAPIResources(data);
	}

	Scene &Renderer::getCurrentScene() const {
		return *currentScene;
	}

	void Renderer::setScene(std::unique_ptr<Scene> scene) {
		currentScene = std::move(scene);
	}

	bool Renderer::hasScene() {
		return currentScene != nullptr;
	}

	void Renderer::renderFrame() {
		if (hasScene()) {
			currentScene->renderFrame();
		}
	}

	Renderer::~Renderer() {
		initializer->destroyGraphicsAPIResources(Cookie::getInstance().getPlatformData());
	}

	void Renderer::prepare() {
		if (hasScene()) {
			currentScene->prepareRendering();
		}
	}

	bool Renderer::isTerminateRequested() {
		if (hasScene()) {
			return currentScene->isTerminateRequested();
		}
		return false;
	}
}