//
//  OpenGLPlatformSpecificData.h
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#ifndef OpenGLPlatformSpecificData_h
#define OpenGLPlatformSpecificData_h
#include "PlatformSpecificData.hpp"
#include "GLFW/glfw3.h"

class OpenGLPlatformSpecificData : public cookie::PlatformSpecificData {
	
private:
	GLFWwindow* window = nullptr;
public:
	GLFWwindow* getWindow() {
		return window;
	}
	
	void setWindow(GLFWwindow* window) {
		this->window = window;
	}
	
	virtual ~OpenGLPlatformSpecificData() {
		
	}
};
#endif /* OpenGLPlatformSpecificData_h */
