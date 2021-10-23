//
// Created by Antiufieiev Michael on 21.10.2021.
//

#include <glm/gtc/type_ptr.hpp>
#include <GLErrorHandler.hpp>
#include "OpenGlCrossBatchBufferStorage.hpp"

void cookie::OpenGLCrossBatchBufferStorage::updateMatrices(const glm::mat4 &projection, const glm::mat4 &view) {
	GLErrorHandler handler;
	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	handler.checkOpenGLError();
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
	handler.checkOpenGLError();
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
	handler.checkOpenGLError();
}

cookie::OpenGLCrossBatchBufferStorage::OpenGLCrossBatchBufferStorage() {
	GLErrorHandler handler;
	glGenBuffers(1, &uboMatrices);
	handler.checkOpenGLError();
	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	handler.checkOpenGLError();
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);
	handler.checkOpenGLError();
}

void cookie::OpenGLCrossBatchBufferStorage::bind() {
	GLErrorHandler handler;
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));
	handler.checkOpenGLError();
}

cookie::OpenGLCrossBatchBufferStorage::~OpenGLCrossBatchBufferStorage() {
	glDeleteBuffers(1, &uboMatrices);
}
