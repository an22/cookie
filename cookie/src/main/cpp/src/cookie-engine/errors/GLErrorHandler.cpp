//
//  GLErrorHandler.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 21.06.2021.
//

#include <cstdlib>
#include <iostream>
#include <EGL/egl.h>
#include "GLErrorHandler.hpp"

GLErrorHandler::GLErrorHandler() = default;

GLErrorHandler::~GLErrorHandler() = default;

void GLErrorHandler::printShaderLog(GLuint shader) {
	int len = 0;
	int chWrittn = 0;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		char *log = (char *) malloc(len);
		glGetShaderInfoLog(shader, len, &chWrittn, log);
		glDeleteShader(shader);
		std::cout << "Shader Info Log: " << log << std::endl;
		free(log);
	}
}

void GLErrorHandler::printProgramLog(int prog) {
	int len = 0;
	int chWrittn = 0;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		char *log = (char *) malloc(len);
		glGetProgramInfoLog(prog, len, &chWrittn, log);
		std::cout << "Program Info Log: " << log << std::endl;
		free(log);
	}
}

bool GLErrorHandler::checkOpenGLError() {
	bool foundError = false;
	GLenum glErr = eglGetError();
	while (glErr != EGL_SUCCESS) {
		std::cout << "glError: " << glErr << std::endl;
		foundError = true;
		glErr = eglGetError();
	}
	return foundError;
}
