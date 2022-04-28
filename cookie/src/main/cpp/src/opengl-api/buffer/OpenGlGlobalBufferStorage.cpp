//
// Created by Antiufieiev Michael on 21.10.2021.
//

#include <glm/gtc/type_ptr.hpp>
#include <GLErrorHandler.hpp>
#include "Cookie.hpp"
#include "OpenGlGlobalBufferStorage.hpp"
#include "OpenGLShader.hpp"
#include "MeshStruct.h"

void OpenGLGlobalBufferStorage::updateMatrices(const glm::mat4 &projection, const glm::mat4 &view) {
	GLErrorHandler handler;
	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	handler.checkOpenGLError();
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
	handler.checkOpenGLError();
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
	handler.checkOpenGLError();
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

OpenGLGlobalBufferStorage::OpenGLGlobalBufferStorage() {
	GLErrorHandler handler;
	glGenBuffers(1, &uboMatrices);
	handler.checkOpenGLError();
	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	handler.checkOpenGLError();
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);
	handler.checkOpenGLError();
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void OpenGLGlobalBufferStorage::bind() {
	GLErrorHandler handler;
	auto& shader = cookie::Cookie::getInstance().getCurrentShader();
	unsigned int matrices_index = glGetUniformBlockIndex(shader.id, "Matrices");
	glUniformBlockBinding(shader.id, matrices_index, 0);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, uboMatrices);
	handler.checkOpenGLError();
}

void OpenGLGlobalBufferStorage::createFaceBuffer() {
	glGenBuffers(1, &ssboFaces);
}

void OpenGLGlobalBufferStorage::createLightBuffer() {
	glGenBuffers(1, &ssboLights);
}

void OpenGLGlobalBufferStorage::createFaceIndexHashesBuffer() {
	glGenBuffers(1, &ssboFaceIndexHashes);
}

void OpenGLGlobalBufferStorage::createFaceIndexesBuffer() {
	glGenBuffers(1, &ssboFaceIndexes);
}

void OpenGLGlobalBufferStorage::createMaterialsBuffer() {
	glGenBuffers(1, &ssboMaterials);
}

OpenGLGlobalBufferStorage::~OpenGLGlobalBufferStorage() {
	glDeleteBuffers(1, &uboMatrices);
	if(ssboFaces != -1) glDeleteBuffers(1, &ssboFaces);
	if(ssboLights != -1) glDeleteBuffers(1, &ssboLights);
	if(ssboFaceIndexes != -1) glDeleteBuffers(1, &ssboFaceIndexes);
	if(ssboFaceIndexHashes != -1) glDeleteBuffers(1, &ssboFaceIndexHashes);
	if(ssboMaterials != -1) glDeleteBuffers(1, &ssboMaterials);
}
