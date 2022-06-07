//
//  EGLPlatformSpecificData.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include "config.hpp"

#if COOKIE_OPENGL

#include "OpenGLPlatformSpecificData.h"

namespace cookie {

	int32_t OpenGLPlatformSpecificData::width() {
		if (_width == 0) {
			glfwGetWindowSize(window, &_width, &_height);
		}
		return _width;
	}

	int32_t OpenGLPlatformSpecificData::height() {
		if (_height == 0) {
			glfwGetWindowSize(window, &_width, &_height);
		}
		return _height;
	}

	GLFWwindow* OpenGLPlatformSpecificData::getWindow() {
		return window;
	}

	void OpenGLPlatformSpecificData::setWindow(GLFWwindow* newWindow) {
		window = newWindow;
	}

	OpenGLPlatformSpecificData::~OpenGLPlatformSpecificData() = default;
}

#endif