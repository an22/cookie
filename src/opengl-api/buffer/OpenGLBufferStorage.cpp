//
//  OpenGLBufferStorage.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include "OpenGLBufferStorage.hpp"
#include "GL/glew.h"
#include "OpenGLPSBufferData.h"

OpenGLBufferStorage::OpenGLBufferStorage() : cookie::BufferStorage() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vboVertex);
	glGenBuffers(1, &vboIndex);
}

OpenGLBufferStorage::~OpenGLBufferStorage() {
	glDeleteBuffers(1, &vboVertex);
	glDeleteBuffers(1, &vboIndex);
	glDeleteVertexArrays(1, &vao);
}

void OpenGLBufferStorage::saveToBuffer(
		const cookie::MeshData &meshData,
		std::unique_ptr<cookie::PlatformSpecificBufferData> data
) {
	auto &_bufferData = dynamic_cast<const OpenGLPSBufferData &>(*data);
	bufferData = std::make_unique<OpenGLPSBufferData>(_bufferData);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vboVertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cookie::Vertex) * meshData.vertices.size(), meshData.vertices.data(),
				 GL_STATIC_DRAW);
	if (!meshData.indices.empty()) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndex);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(meshData.indices[0]) * meshData.indices.size(),
					 meshData.indices.data(), GL_STATIC_DRAW);
	}
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(cookie::Vertex), nullptr);
	glEnableVertexAttribArray(0);
}

void OpenGLBufferStorage::bind() {
	glBindVertexArray(vao);
}
