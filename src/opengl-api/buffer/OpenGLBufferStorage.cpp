//
//  OpenGLBufferStorage.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include "OpenGLBufferStorage.hpp"
#include "GL/glew.h"
#include "OpenGLPSBufferData.h"
#include "GLErrorHandler.hpp"

OpenGLBufferStorage::OpenGLBufferStorage() : cookie::BufferStorage() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vboVertex);
	glGenBuffers(1, &vboIndex);
	glGenBuffers(1, &vboMatrices);
	glGenTextures(1, &tboMatrices);
}

OpenGLBufferStorage::~OpenGLBufferStorage() {
	glDeleteBuffers(1, &vboVertex);
	glDeleteBuffers(1, &vboIndex);
	glDeleteBuffers(1, &vboMatrices);
	glDeleteTextures(1, &tboMatrices);
	glDeleteVertexArrays(1, &vao);
}

void OpenGLBufferStorage::saveToBuffer(
		const cookie::MeshData &meshData,
		const std::vector<glm::mat4>& matrices,
		std::unique_ptr<cookie::PlatformSpecificBufferData> data
) const {
	auto &_bufferData = dynamic_cast<const OpenGLPSBufferData &>(*data);
	glBindVertexArray(vao);

	setupVertexElementBuffer(meshData);
	setupMatricesBuffer(matrices);

	glBindVertexArray(0);
}

inline void OpenGLBufferStorage::setupVertexElementBuffer(const cookie::MeshData &meshData) const {
	GLErrorHandler handler;
	glBindBuffer(GL_ARRAY_BUFFER, vboVertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cookie::Vertex) * meshData.vertices.size(), meshData.vertices.data(), GL_STATIC_DRAW);
	handler.checkOpenGLError();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndex);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshData.indices.size() * sizeof(unsigned int), meshData.indices.data(), GL_STATIC_DRAW);
	handler.checkOpenGLError();
	// vertex coords
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(cookie::Vertex), (void*)nullptr);
	handler.checkOpenGLError();
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(cookie::Vertex), (void*)offsetof(cookie::Vertex, normal));
	handler.checkOpenGLError();
	// vertex texture coords
	glEnableVertexAttribArray(2);
	handler.checkOpenGLError();
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(cookie::Vertex), (void*)offsetof(cookie::Vertex, texCoords));
	handler.checkOpenGLError();
	glEnableVertexAttribArray(3);
	handler.checkOpenGLError();
	glVertexAttribPointer(3, 1, GL_INT, GL_FALSE, sizeof(cookie::Vertex), (void*)offsetof(cookie::Vertex, matrixOffset));
	handler.checkOpenGLError();
}

inline void OpenGLBufferStorage::setupMatricesBuffer(const std::vector<glm::mat4>& matrices) const {
	GLErrorHandler handler;
	glBindBuffer(GL_TEXTURE_BUFFER, vboMatrices);
	handler.checkOpenGLError();
	glBufferData(GL_TEXTURE_BUFFER, sizeof(glm::mat4) * matrices.size(), matrices.data(), GL_STATIC_DRAW);
	handler.checkOpenGLError();
	glActiveTexture(GL_TEXTURE0);
	handler.checkOpenGLError();
	glBindTexture(GL_TEXTURE_BUFFER, tboMatrices);
	handler.checkOpenGLError();
	glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, vboMatrices);
	handler.checkOpenGLError();
}

void OpenGLBufferStorage::bind() const {
	GLErrorHandler handler;
	glBindVertexArray(vao);
	handler.checkOpenGLError();
}
