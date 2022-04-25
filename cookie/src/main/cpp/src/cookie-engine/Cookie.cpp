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
		initializer->initGraphicsAPIResources(*platformData);
		defaultShader = CookieFactory::provideShader(
				STRCAT(BASE_DIR, "shader/vertex/vertex.glsl"),
				STRCAT(BASE_DIR, "shader/fragment/fragment.glsl")
		);
	}

	void Cookie::clear() {
		initializer->destroyGraphicsAPIResources(*platformData);
	}

	Scene &Cookie::getCurrentScene() const {
		return *currentScene;
	}
}
