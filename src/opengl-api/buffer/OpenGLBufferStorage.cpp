//
//  OpenGLBufferStorage.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include <MacTypes.h>
#include "OpenGLBufferStorage.hpp"
#include "GL/glew.h"
#include "OpenGLPSBufferData.h"

OpenGLBufferStorage::OpenGLBufferStorage() : cookie::BufferStorage() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vboVertex);
	glGenBuffers(1, &vboIndex);
	glGenBuffers(1, &tboMatrices);
	glGenTextures(1, &tboTexture);
}

OpenGLBufferStorage::~OpenGLBufferStorage() {
	glDeleteBuffers(1, &vboVertex);
	glDeleteBuffers(1, &vboIndex);
	glDeleteBuffers(1, &tboMatrices);
	glDeleteTextures(1, &tboTexture);
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
	glBindBuffer(GL_ARRAY_BUFFER, vboVertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cookie::Vertex) * meshData.vertices.size(), meshData.vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndex);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshData.indices.size() * sizeof(uint32_t), meshData.indices.data(), GL_STATIC_DRAW);

	// vertex coords
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(cookie::Vertex), (void*)nullptr);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(cookie::Vertex), (void*)offsetof(cookie::Vertex, normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(cookie::Vertex), (void*)offsetof(cookie::Vertex, texCoords));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 1, GL_UNSIGNED_INT, GL_FALSE, sizeof(cookie::Vertex), (void*)offsetof(cookie::Vertex, matrixOffset));
}

inline void OpenGLBufferStorage::setupMatricesBuffer(const std::vector<glm::mat4>& matrices) const {
	glBindBuffer(GL_TEXTURE_BUFFER, tboMatrices);
	glBufferData(GL_TEXTURE_BUFFER, sizeof(glm::mat4) * matrices.size(), matrices.data(), GL_STATIC_DRAW);
	glBindTexture(GL_TEXTURE_BUFFER, tboTexture);
	glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, tboMatrices);
}

void OpenGLBufferStorage::bind() const {
	glBindVertexArray(vao);
}
