//
//  Cookie.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include "Cookie.hpp"

namespace cookie {
	Cookie *engine = nullptr;

	void init(CgAPI api) {
		engine = new Cookie(api);
		engine->initializer->initGraphicsAPIResources();
	}

	void setScene(std::unique_ptr<Scene> scene) {
		engine->currentScene = std::move(scene);
	}

	void destroy() {
		delete engine;
	}

	CgAPI Cookie::CURRENT_CG_API = CgAPI::OpenGL;

	Cookie::Cookie(CgAPI api)
			: platformData(CookieFactory::createPlatformSpecificContainer()),
			  initializer(CookieFactory::provideInitializer()) {
		CURRENT_CG_API = api;
	}
}
