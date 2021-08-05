//
//  Cookie.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include <stdio.h>
#include "Cookie.h"

namespace cookie {
Cookie* engine = nullptr;

void init(CgAPI api) {
	engine = new Cookie(api);
	engine->initializer->initGraphicsAPIResources();
}

void destroy() {
	delete engine;
}

CgAPI Cookie::CURRENT_CG_API = CgAPI::OpenGL;

Cookie::Cookie(CgAPI api) {
	CURRENT_CG_API = api;
	platformData = CookieFactory::createPlatformSpecificContainer();
	initializer = CookieFactory::provideInitializer();
}
}
