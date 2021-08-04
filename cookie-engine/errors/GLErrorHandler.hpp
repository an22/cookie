//
//  GLErrorHandler.hpp
//  lighting-test
//
//  Created by Antiufieiev Michael on 21.06.2021.
//

#ifndef GLErrorHandler_hpp
#define GLErrorHandler_hpp

#include <stdio.h>
#include <iostream>
#include <GL/glew.h>

#endif /* GLErrorHandler_hpp */
class GLErrorHandler {

public :
	GLErrorHandler();
	~GLErrorHandler();
	
	void printShaderLog(GLuint shader);
	void printProgramLog(int prog);
	bool checkOpenGLError();
	void errorCallback(int code, const char* description);
	
};
