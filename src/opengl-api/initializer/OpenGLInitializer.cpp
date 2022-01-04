//
//  OpenGLInitializer.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "OpenGLInitializer.hpp"
#include "OpenGLPlatformSpecificData.h"
#include "Cookie.hpp"

void windowReshapeCallback(GLFWwindow *window, int newWidth, int newHeight) {
	glViewport(0, 0, newWidth, newHeight); // sets screen region associated with framebuffer
	cookie::Cookie::getInstance().currentScene->getSettings().onWindowResized(newWidth, newHeight);
}

void errorCallback(int code, const char *description) {
	//TODO proper error handling
	std::cout << description << std::endl;
}

void OpenGLInitializer::initGraphicsAPIResources(cookie::PlatformSpecificData& data) const {
	if (!glfwInit()) exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwSetErrorCallback(errorCallback);
	GLFWwindow *window = glfwCreateWindow(600, 600, "EngineTest", nullptr, nullptr);
	glfwSetFramebufferSizeCallback(window, windowReshapeCallback);
	auto &platformData = dynamic_cast<OpenGLPlatformSpecificData &>(data);
	platformData.setWindow(window);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) exit(EXIT_FAILURE);
	glfwSwapInterval(1);
}

void OpenGLInitializer::destroyGraphicsAPIResources(cookie::PlatformSpecificData& data) const {
	auto &platformData = dynamic_cast<OpenGLPlatformSpecificData &>(data);
	glfwDestroyWindow(platformData.getWindow());
	glfwTerminate();
}
