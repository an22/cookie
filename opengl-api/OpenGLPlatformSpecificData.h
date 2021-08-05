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
	virtual int32_t width();
	virtual int32_t height();
	
	GLFWwindow* getWindow();
	void setWindow(GLFWwindow* window);

	virtual ~OpenGLPlatformSpecificData();
};
#endif /* OpenGLPlatformSpecificData_h */
