//
//  GLErrorHandler.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 21.06.2021.
//
#include "config.hpp"

#if COOKIE_OPENGL

#include <cstdlib>
#include <iostream>
#include "GLErrorHandler.hpp"
#include "Macro.h"

namespace cookie {
	void GLErrorHandler::printShaderLog(uint32_t shader) {
#ifndef NDEBUG
		int bufSize = 0;
		int length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);
		if (bufSize > 0) {
			char *log = (char *) malloc(bufSize);
			glGetShaderInfoLog(shader, bufSize, &length, log);
			LOG_I("Shader Info Log: %s", log);
			glDeleteShader(shader);
			free(log);
		}
#endif
	}

	void GLErrorHandler::printProgramLog(int32_t prog) {
#ifndef NDEBUG
		int bufSize = 0;
		int length = 0;
		glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &bufSize);
		if (bufSize > 0) {
			char *log = (char *) malloc(bufSize);
			glGetProgramInfoLog(prog, bufSize, &length, log);
			LOG_I("Program Info Log: %s", log);
			free(log);
		}
#endif
	}
}

#endif
