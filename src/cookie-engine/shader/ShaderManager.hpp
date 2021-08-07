//
//  ShaderManager.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 04.07.2021.
//

#ifndef ShaderManager_hpp
#define ShaderManager_hpp

#include <GL/glew.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "GLErrorHandler.hpp"

class ShaderManager {

public:
    static GLuint createShaderProgram();
    static GLuint loadShaderFrom(GLErrorHandler &errorHandler, std::string path, GLenum shaderType);
};

#endif /* ShaderManager_hpp */
