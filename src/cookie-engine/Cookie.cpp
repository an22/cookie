//
//  Cookie.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include "Cookie.hpp"

namespace cookie {
	Cookie *engine = nullptr;
	Shader *defaultShader = nullptr;

	void init(CgAPI api) {
		engine = new Cookie(api);
		engine->initializer->initGraphicsAPIResources();
		defaultShader = CookieFactory::provideShader(
				"/Users/antiufieievmichael/Guides/cookie-engine/src/cookie-engine/shader/vertex/vertex.glsl",
				"/Users/antiufieievmichael/Guides/cookie-engine/src/cookie-engine/shader/fragment/fragment.glsl"
		).release();
	}

	void setScene(std::shared_ptr<Scene> scene) {
		engine->currentScene = std::shared_ptr(std::move(scene));
	}

	void destroy() {
		delete defaultShader;
		delete engine;
	}

	CgAPI Cookie::CURRENT_CG_API = CgAPI::OpenGL;

	Cookie::Cookie(CgAPI api)
			: platformData(CookieFactory::createPlatformSpecificContainer()),
			  initializer(CookieFactory::provideInitializer()) {
		CURRENT_CG_API = api;
	}
}
