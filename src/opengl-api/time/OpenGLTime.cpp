//
//  OpenGLTime.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include "OpenGLTime.hpp"
#include <GLFW/glfw3.h>

double OpenGLTime::getProgramTime() {
	return glfwGetTime();
}

double OpenGLTime::getFrameTime() {
	return 0.0;//TODO
}
