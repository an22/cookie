//
//  Cookie.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include <Cube.hpp>
#include "Cookie.hpp"
#include "CookieFactory.hpp"

namespace cookie {

	std::mutex Cookie::mutex;
	std::unique_ptr<Cookie> Cookie::instance;

	Cookie::Cookie(CgAPI api) : platformData(CookieFactory::createPlatformSpecificContainer()),
								initializer(CookieFactory::provideInitializer()) {
		currentAPI = api;
	}

	void Cookie::setScene(std::unique_ptr<Scene> scene) {
		currentScene = std::move(scene);
	}

	Cookie &Cookie::getInstance(CgAPI api) {
		std::lock_guard<std::mutex> lock(mutex);
		if (Cookie::instance == nullptr) {
			Cookie::instance = std::unique_ptr<Cookie>(new Cookie(api));
		}
		return *Cookie::instance;
	}

	void Cookie::prepareRendering() {
		initializer->initGraphicsAPIResources(*platformData);
		currentShader = CookieFactory::provideShader(
				"shader/vertex/vertex.glsl",
				"shader/fragment/fragment.glsl"
		);
		setScene(std::make_unique<cookie::Scene>());
		getCurrentScene().addObject(std::make_shared<cookie::Cube>(0.0f, 0.0f, 0.0f));
	}

	void Cookie::startRendering() {
		renderingLoop = new std::thread(&Cookie::loopInternal, this);
	}

	void Cookie::loopInternal() {
		prepareRendering();
		auto &scene = getCurrentScene();
		scene.prepareRendering();
		while (!terminate) {
			std::lock_guard lock(localMutex);
			scene.renderFrame();
		}
	}

	void Cookie::clear() {
		localMutex.lock();
		terminate = true;
		localMutex.unlock();
		renderingLoop->join();
		initializer->destroyGraphicsAPIResources(*platformData);
	}

	Scene &Cookie::getCurrentScene() const {
		return *currentScene;
	}
}
