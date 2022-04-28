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

bool start(EGLNativeWindowType window) {
	cookie::Cookie &engine = cookie::Cookie::getInstance(CgAPI::OpenGL);
	try {
		auto &eglData = engine.getPlatformData<OpenGLPlatformSpecificData>();
		eglData.setWindow(window);
		engine.prepareRendering();
		engine.setScene(std::make_unique<cookie::Scene>());
		engine.getCurrentScene().addObject(std::make_shared<cookie::Cube>(0.0f, 0.0f, 400.0f));
		engine.getCurrentScene().startLoop();
		engine.clear();
		return true;
	}
	catch (std::exception &e) {
		engine.clear();
		std::cout << e.what() << std::endl;
		return false;
	}
}