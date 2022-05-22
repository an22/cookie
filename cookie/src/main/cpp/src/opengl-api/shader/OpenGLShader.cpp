//
//  OpenGLShader.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include "OpenGLShader.hpp"
#include <GLES3/gl32.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include "CookieFactory.hpp"
#include "GLErrorHandler.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

namespace cookie {
	OpenGLShader::OpenGLShader(const std::string &vertexPath, const std::string &fragmentPath)
			: cookie::Shader() {
		auto vertex = loadShaderFrom(vertexPath, GL_VERTEX_SHADER);
		auto fragment = loadShaderFrom(fragmentPath, GL_FRAGMENT_SHADER);
		id = static_cast<int32_t>(glCreateProgram());
		glAttachShader(id, vertex);
		glAttachShader(id, fragment);
		glLinkProgram(id);
		GLint linked;
		glGetProgramiv(id, GL_LINK_STATUS, &linked);
		if (linked != 1) {
			throw std::runtime_error("Program linking failed");
		}
	}

	OpenGLShader::OpenGLShader(const std::string &computePath) {
		auto compute = loadShaderFrom(computePath, GL_COMPUTE_SHADER);
		id = static_cast<int32_t>(glCreateProgram());
		glAttachShader(id, compute);
		glLinkProgram(id);
		GLint linked;
		glGetProgramiv(id, GL_LINK_STATUS, &linked);
		if (linked != 1) {
			throw std::runtime_error("Program linking failed");
		}
	}

	GLuint OpenGLShader::loadShaderFrom(const std::string &path, GLenum shaderType) {
		GLuint shader = glCreateShader(shaderType);
		size_t size;
		const char *shaderCode = reinterpret_cast<char *>(
				cookie::CookieFactory::getManager().readEntireFile(path, size, true)
		);
		glShaderSource(shader, 1, &shaderCode, nullptr);
		glCompileShader(shader);
		GLint shaderCompiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompiled);

		delete[] shaderCode;
		if (shaderCompiled != GL_TRUE) {
			throw std::runtime_error("Shader compilation failed at: " + path);
		}
		GLErrorHandler::checkOpenGLError();
		return shader;
	}

	void OpenGLShader::use() {
		glUseProgram(id);
	}

	void OpenGLShader::setBool(const std::string &name, bool value) const {
		GLint location = glGetUniformLocation(id, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::setInt(const std::string &name, int32_t value) const {
		GLint location = glGetUniformLocation(id, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::setFloat(const std::string &name, float value) const {
		GLint location = glGetUniformLocation(id, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::setMatrix4(const std::string &name, const glm::mat4 &matrix) const {
		GLint location = glGetUniformLocation(id, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}
