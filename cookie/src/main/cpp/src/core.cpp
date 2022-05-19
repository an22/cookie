//
// core.cpp
// cookie-engine
//
//  Created by Antiufieiev Michael on 21.06.2021.
//

#include <iostream>
#include <OpenGLPlatformSpecificData.h>
#include "EGL/egl.h"
#include "Cookie.hpp"
#include "Cube.hpp"
#include "core.hpp"

bool start() {
	cookie::Cookie &engine = cookie::Cookie::getInstance(CgAPI::OpenGL);
	try {
		engine.setScene(std::make_unique<cookie::Scene>());
		engine.getCurrentScene().addObject(std::make_shared<cookie::Cube>(0.0f, 0.0f, 400.0f));
		return true;
	}
	catch (std::exception &e) {
		engine.clear();
		std::cout << e.what() << std::endl;
		return false;
	}
}