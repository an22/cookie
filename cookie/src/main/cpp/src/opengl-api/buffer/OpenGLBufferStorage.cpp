//
//  OpenGLBufferStorage.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include <EGL/egl.h>
#include <GLES3/gl32.h>
#include <OpenGLShader.hpp>
#include <Cookie.hpp>
#include "OpenGLBufferStorage.hpp"
#include "Material.h"
#include "GLErrorHandler.hpp"

OpenGLBufferStorage::OpenGLBufferStorage() : cookie::BufferStorage() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vboVertex);
	glGenBuffers(1, &uboMaterial);
	glGenBuffers(1, &vboIndex);
	glGenBuffers(1, &tboMatrices);
	glGenTextures(1, &texMatrices);
}

OpenGLBufferStorage::~OpenGLBufferStorage() {
	glDeleteBuffers(1, &vboVertex);
	glDeleteBuffers(1, &uboMaterial);
	glDeleteBuffers(1, &vboIndex);
	glDeleteBuffers(1, &tboMatrices);
	glDeleteTextures(1, &texMatrices);
	glDeleteVertexArrays(1, &vao);
}

void OpenGLBufferStorage::saveToBuffer(
		const cookie::MeshData &meshData,
		const std::vector<glm::mat4> &matrices,
		std::unique_ptr<cookie::PlatformSpecificBufferData> data
) const {
	auto &_bufferData = dynamic_cast<const OpenGLPSBufferData &>(*data);

	setupVertexElementBuffer(meshData);
	setupMaterialBuffer(meshData);
	setupMatricesBuffer(matrices);
}

inline void OpenGLBufferStorage::setupVertexElementBuffer(const cookie::MeshData &meshData) const {
	glBindVertexArray(vao);
	GLErrorHandler handler;
	glBindBuffer(GL_ARRAY_BUFFER, vboVertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cookie::Vertex) * meshData.vertices.size(), meshData.vertices.data(),
				 GL_STATIC_DRAW);
	handler.checkOpenGLError();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndex);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshData.indices.size() * sizeof(unsigned int), meshData.indices.data(),
				 GL_STATIC_DRAW);
	handler.checkOpenGLError();
	// vertex coords
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(cookie::Vertex), (void *) nullptr);
	handler.checkOpenGLError();
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(cookie::Vertex), (void *) offsetof(cookie::Vertex, normal));
	handler.checkOpenGLError();
	// vertex texture coords
	glEnableVertexAttribArray(2);
	handler.checkOpenGLError();
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(cookie::Vertex),
						  (void *) offsetof(cookie::Vertex, texCoords));
	handler.checkOpenGLError();
	glEnableVertexAttribArray(3);
	handler.checkOpenGLError();
	glVertexAttribIPointer(3, 1, GL_INT, sizeof(cookie::Vertex), (void *) offsetof(cookie::Vertex, matrixOffset));
	handler.checkOpenGLError();
	glBindVertexArray(0);
}

inline void OpenGLBufferStorage::setupMatricesBuffer(const std::vector<glm::mat4> &matrices) const {
	GLErrorHandler handler;
	glBindBuffer(GL_TEXTURE_BUFFER, tboMatrices);
	handler.checkOpenGLError();
	glBufferData(GL_TEXTURE_BUFFER, sizeof(glm::mat4) * matrices.size(), matrices.data(), GL_STATIC_DRAW);
	handler.checkOpenGLError();
	glBindTexture(GL_TEXTURE_BUFFER, texMatrices);
	handler.checkOpenGLError();
	glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, tboMatrices);
	handler.checkOpenGLError();
	glBindBuffer(GL_TEXTURE_BUFFER, 0);
}

void OpenGLBufferStorage::setupMaterialBuffer(const cookie::MeshData &meshData) const {
	GLErrorHandler handler;
	glBindBuffer(GL_UNIFORM_BUFFER, uboMaterial);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(cookie::GPUMaterial), (void *) ((char*)meshData.material.get() + offsetof(cookie::Material, diffuseColor)), GL_STATIC_DRAW);
	handler.checkOpenGLError();
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void OpenGLBufferStorage::bind() const {
	GLErrorHandler handler;
	glBindVertexArray(vao);
	glBindBuffer(GL_TEXTURE_BUFFER, tboMatrices);
	glBindTexture(GL_TEXTURE_BUFFER, texMatrices);
	glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, tboMatrices);
	glBindBuffer(GL_UNIFORM_BUFFER, uboMaterial);
	auto& shader = cookie::Cookie::getInstance().getDefaultShader<OpenGLShader>();
	unsigned int matrices_index = glGetUniformBlockIndex(shader.id, "Material");
	glUniformBlockBinding(shader.id, matrices_index, 1);
	handler.checkOpenGLError();
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, uboMaterial);
}

void OpenGLBufferStorage::unbind() const {
	GLErrorHandler handler;
	glBindVertexArray(0);
	glBindBuffer(GL_TEXTURE_BUFFER, 0);
	glBindTexture(GL_TEXTURE_BUFFER, 0);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	handler.checkOpenGLError();
}
