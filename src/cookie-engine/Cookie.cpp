//
//  Cookie.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include "Cookie.hpp"
#include "CookieFactory.hpp"

namespace cookie {

	std::mutex Cookie::mutex;
	std::unique_ptr<Cookie> Cookie::instance;

	Cookie::Cookie(CgAPI api)
			: platformData(CookieFactory::createPlatformSpecificContainer()),
			  initializer(CookieFactory::provideInitializer()) {
		currentAPI = api;
		initializer->initGraphicsAPIResources(*platformData);
		defaultShader = CookieFactory::provideShader(
				"src/cookie-engine/shader/vertex/vertex.glsl",
				"src/cookie-engine/shader/fragment/fragment.glsl"
		);
	}

	void Cookie::setScene(std::shared_ptr<Scene> scene) {
		currentScene = std::shared_ptr(std::move(scene));
	}

	Cookie::~Cookie() = default;

	Cookie &Cookie::getInstance(CgAPI api) {
		std::lock_guard<std::mutex> lock(mutex);
		CookieFactory::getFactory(api);
		if(Cookie::instance == nullptr) {
			Cookie::instance = std::unique_ptr<Cookie>(new Cookie(api));
		}
		return *Cookie::instance;
	}
}
