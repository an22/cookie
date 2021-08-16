//
//  OpenGLShader.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include "OpenGLShader.hpp"
#include "GLErrorHandler.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <sstream>

OpenGLShader::OpenGLShader(const std::string &vertexPath, const std::string &fragmentPath) : cookie::Shader() {
	auto vertex = loadShaderFrom(vertexPath, GL_VERTEX_SHADER);
	auto fragment = loadShaderFrom(fragmentPath, GL_FRAGMENT_SHADER);
	renderingProgram = glCreateProgram();
	glAttachShader(renderingProgram, vertex);
	glAttachShader(renderingProgram, fragment);
	glLinkProgram(renderingProgram);
	GLint linked;
	glGetProgramiv(renderingProgram, GL_LINK_STATUS, &linked);
	if (linked != 1) {
		throw std::runtime_error("Program linking failed");
	}
}

GLuint OpenGLShader::loadShaderFrom(const std::string &path, GLenum shaderType) {
	std::ifstream filestream(path, std::ios::in);
	if (!filestream.is_open()) {
		throw std::invalid_argument("Cant read " + path);
	}

	std::stringstream buffer;
	buffer << filestream.rdbuf();
	filestream.close();
	std::string result = buffer.str();
	GLuint shader = glCreateShader(shaderType);
	const char *shaderCode = result.c_str();
	glShaderSource(shader, 1, &shaderCode, nullptr);
	glCompileShader(shader);
	GLint shaderCompiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompiled);
	if (shaderCompiled != 1) {
		throw std::runtime_error("Shader compilation failed");
	}
	return shader;
}

void OpenGLShader::use() {
	glUseProgram(renderingProgram);
}

void OpenGLShader::setBool(const std::string &name, bool value) const {
	GLint location = glGetUniformLocation(renderingProgram, name.c_str());
	glUniform1i(location, value);
}

void OpenGLShader::setInt(const std::string &name, int32_t value) const {
	GLint location = glGetUniformLocation(renderingProgram, name.c_str());
	glUniform1i(location, value);
}

void OpenGLShader::setFloat(const std::string &name, float value) const {
	GLint location = glGetUniformLocation(renderingProgram, name.c_str());
	glUniform1f(location, value);
}

void OpenGLShader::setMatrix4(const std::string &name, glm::mat4 &matrix) {
	GLint location = glGetUniformLocation(renderingProgram, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
