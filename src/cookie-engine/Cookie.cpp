//
//  Cookie.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include "Cookie.hpp"
#include "CookieFactory.hpp"
#include "Macro.h"

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
		std::lock_guard lock(localMutex);
		initializer->initGraphicsAPIResources(*platformData);
		currentScene = std::make_unique<Scene>();//TODO DELETE
		if (currentScene) {
			currentScene->prepareRendering();
		} else {
			throw std::runtime_error("No scene to render. ABORT");
		}
	}

	void Cookie::startRendering() {
		renderingLoop = std::make_unique<std::thread>(&Cookie::loopInternal, this);
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
		pthread_setname_np(renderingLoop->native_handle(), "CookieRenderer");
#endif
#ifdef WIN32
		renderingLoop->join();
#endif
	}

	void Cookie::loopInternal() {
		try {
			prepareRendering();
			while (true) {
				std::lock_guard lock(localMutex);
				if (terminate || currentScene->isTerminateRequested()) {
					terminateInternal();
					break;
				}
				currentScene->renderFrame();
			}
		} catch (const std::exception &e) {
			LOG_E("%s", e.what());
			clearInternal();
		}
	}

	void Cookie::terminateInternal() {
		terminate = false;
		initializer->destroyGraphicsAPIResources(*platformData);
	}

	void Cookie::clearInternal() {
		std::lock_guard lock(localMutex);
		terminate = true;
	}

	void Cookie::clear() {
		clearInternal();
		renderingLoop->join();
	}

	Scene &Cookie::getCurrentScene() const {
		return *currentScene;
	}

	void Cookie::onWindowResized(int32_t width, int32_t height) {
		std::lock_guard lock(localMutex);
		if (terminate) return;
		platformData->setWidth(width);
		platformData->setHeight(height);
		if (currentScene) {
			currentScene->resize(width, height);
		}
	}
}
