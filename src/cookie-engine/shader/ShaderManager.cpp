//
//  ShaderManager.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 04.07.2021.
//

#include "ShaderManager.hpp"

GLuint ShaderManager::createShaderProgram() {
    GLErrorHandler errorHandler;
    auto vertex = loadShaderFrom(errorHandler,
                                 "/Users/antiufieievmichael/Guides/lighting-test/lighting-test/shader/vertex/24cubes.glsl",
                                 GL_VERTEX_SHADER);
    auto fragment = loadShaderFrom(errorHandler,
                                   "/Users/antiufieievmichael/Guides/lighting-test/lighting-test/shader/fragment/fragment.glsl",
                                   GL_FRAGMENT_SHADER);
    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vertex);
    glAttachShader(vfProgram, fragment);
    glLinkProgram(vfProgram);
    errorHandler.checkOpenGLError();
    GLint linked;
    glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
    if (linked != 1) {
        errorHandler.printProgramLog(vfProgram);
        throw "Program linking failed";
    }
    return vfProgram;
}

GLuint ShaderManager::loadShaderFrom(GLErrorHandler &errorHandler, std::string path, GLenum shaderType) {
    std::ifstream filestream(path, std::ios::in);
    if (!filestream.is_open()) {
        throw "Cant read " + path;
    }

    std::stringstream buffer;
    buffer << filestream.rdbuf();
    filestream.close();
    std::string result = buffer.str();
    const char *shaderCode = result.c_str();
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);
    errorHandler.checkOpenGLError();
    GLint shaderCompiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompiled);
    if (shaderCompiled != 1) {
        errorHandler.printShaderLog(shader);
        throw "Shader compilation failed";
    }
    return shader;
}
