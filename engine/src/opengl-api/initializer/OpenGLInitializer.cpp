//
//  EGLInitializer.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//
#include "config.hpp"

#if COOKIE_OPENGL

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "GLErrorHandler.hpp"
#include "OpenGLInitializer.hpp"
#include "OpenGLPlatformSpecificData.h"
#include "Cookie.hpp"
#include "Macro.h"

namespace cookie {

	void windowReshapeCallback(GLFWwindow *window, int newWidth, int newHeight) {
		cookie::Cookie::getInstance().onWindowResized(newWidth, newHeight);
	}

	void errorCallback(int code, const char *description) {
		LOG_E(code + description);
	}

	void OpenGLInitializer::initGraphicsAPIResources(cookie::PlatformSpecificData &data) const {
		if (!glfwInit()) { exit(EXIT_FAILURE); }
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwSetErrorCallback(errorCallback);
		GLFWwindow *window = glfwCreateWindow(1600, 1600, "EngineTest", nullptr, nullptr);
		glfwSetFramebufferSizeCallback(window, windowReshapeCallback);
		auto &platformData = dynamic_cast<OpenGLPlatformSpecificData &>(data);
		platformData.setWindow(window);
		glfwMakeContextCurrent(window);
		if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
		glfwSwapInterval(1);
		GLErrorHandler::checkOpenGLError();
	}

	void OpenGLInitializer::destroyGraphicsAPIResources(cookie::PlatformSpecificData &data) const {
		auto &platformData = dynamic_cast<OpenGLPlatformSpecificData &>(data);
		glfwDestroyWindow(platformData.getWindow());
		glfwTerminate();
	}
}

#endif