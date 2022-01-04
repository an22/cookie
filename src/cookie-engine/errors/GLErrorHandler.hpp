//
//  GLErrorHandler.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 21.06.2021.
//

#ifndef GLErrorHandler_hpp
#define GLErrorHandler_hpp

#include <GL/glew.h>

class GLErrorHandler {

public :
	GLErrorHandler();
	~GLErrorHandler();

	void printShaderLog(GLuint shader);
	void printProgramLog(int prog);
	bool checkOpenGLError();
};

#endif /* GLErrorHandler_hpp */
