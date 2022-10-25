//
//  Cookie.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include "Cookie.hpp"
#include "CookieFactory.hpp"
#include "Macro.h"
#include "Renderer.hpp"
#include "Scene.hpp"

namespace cookie {

	std::mutex Cookie::mutex;
	std::unique_ptr<Cookie> Cookie::instance;

	Cookie::Cookie(CgAPI api) : platformData(CookieFactory::createPlatformSpecificContainer()),
								currentAPI(api),
								renderer(std::make_unique<Renderer>(*platformData)){
	}

	Cookie &Cookie::getInstance(CgAPI api) {
		std::lock_guard<std::mutex> lock(mutex);
		if (Cookie::instance == nullptr) {
			Cookie::instance = std::unique_ptr<Cookie>(new Cookie(api));
		}
		return *Cookie::instance;
	}

	void Cookie::startRendering() {
		loopInternal();
	}

	void Cookie::loopInternal() {
		try {
			renderer->prepare();
			while (true) {
				std::lock_guard lock(localMutex);
				if (terminate || renderer->isTerminateRequested()) {
					break;
				}
				renderer->renderFrame();
			}
		} catch (const std::exception &e) {
			LOG_E("%s", e.what());
			clearInternal();
		}
	}

	void Cookie::clearInternal() {
		std::lock_guard lock(localMutex);
		terminate = true;
	}

	void Cookie::clear() {
		clearInternal();
	}

	void Cookie::onWindowResized(int32_t width, int32_t height) {
		std::lock_guard lock(localMutex);
		if (terminate) { return; }
		platformData->setWidth(width);
		platformData->setHeight(height);
		if (renderer->hasScene()) {
			renderer->getCurrentScene().resize(width, height);
		}
	}

	void Cookie::setScene(std::unique_ptr<Scene> scene) {
		renderer->setScene(std::move(scene));
	}
}
