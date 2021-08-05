//
//  OpenGLPlatformSpecificData.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include <stdio.h>
#include "OpenGLPlatformSpecificData.h"
#include "GLFW/glfw3.h"

int32_t OpenGLPlatformSpecificData::width() {
	if(_width == 0) {
		glfwGetWindowSize(window, &_width, &_height);
	}
	return _width;
}

int32_t OpenGLPlatformSpecificData::height() {
	if(_height == 0) {
		glfwGetWindowSize(window, &_width, &_height);
	}
	return _height;
}

GLFWwindow* OpenGLPlatformSpecificData::getWindow() {
	return window;
}

void OpenGLPlatformSpecificData::setWindow(GLFWwindow* window) {
	this->window = window;
}

OpenGLPlatformSpecificData::~OpenGLPlatformSpecificData() {
	
}
