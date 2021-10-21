//
// Created by Antiufieiev Michael on 21.10.2021.
//

#include <glm/gtc/type_ptr.hpp>
#include "OpenGlCrossBatchBufferStorage.hpp"

void cookie::OpenGLCrossBatchBufferStorage::updateMatrices(const glm::mat4 &projection, const glm::mat4 &view) {
	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
}

cookie::OpenGLCrossBatchBufferStorage::OpenGLCrossBatchBufferStorage() {
	glGenBuffers(1, &uboMatrices);
	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);
}

void cookie::OpenGLCrossBatchBufferStorage::bind() {
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));
}

cookie::OpenGLCrossBatchBufferStorage::~OpenGLCrossBatchBufferStorage() {
	glDeleteBuffers(1, &uboMatrices);
}
