//
//  OpenGLBufferStorage.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//
#include "config.hpp"

#if COOKIE_EGL

#include <EGL/egl.h>
#include <GLES3/gl32.h>
#include "EGLPSBufferData.h"
#include "EGLBufferStorage.hpp"
#include "EGLErrorHandler.hpp"

namespace cookie {
	EGLBufferStorage::EGLBufferStorage() : cookie::BufferStorage() {
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vboVertex);
		glGenBuffers(1, &uboMaterial);
		glGenBuffers(1, &vboIndex);
		glGenBuffers(1, &sboMatrices);
	}

	EGLBufferStorage::~EGLBufferStorage() {
		glDeleteBuffers(1, &vboVertex);
		glDeleteBuffers(1, &uboMaterial);
		glDeleteBuffers(1, &vboIndex);
		glDeleteBuffers(1, &sboMatrices);
		glDeleteVertexArrays(1, &vao);
	}

	void EGLBufferStorage::saveToBuffer(
			const cookie::MeshData &meshData,
			const std::vector<glm::mat4> &matrices,
			std::unique_ptr<cookie::PlatformSpecificBufferData> data
	) const {
		setupVertexElementBuffer(meshData);
		setupMaterialBuffer(meshData);
		setupMatricesBuffer(matrices);
	}

	inline void EGLBufferStorage::setupVertexElementBuffer(const cookie::MeshData &meshData) const {
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vboVertex);
		glBufferData(
				GL_ARRAY_BUFFER,
				sizeof(cookie::Vertex) * meshData.vertices.size(),
				meshData.vertices.data(),
				GL_STATIC_DRAW
		);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndex);
		glBufferData(
				GL_ELEMENT_ARRAY_BUFFER,
				meshData.indices.size() * sizeof(unsigned int),
				meshData.indices.data(),
				GL_STATIC_DRAW
		);
		// vertex coords
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(cookie::Vertex), (void *) nullptr);
		// vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(
				1,
				3,
				GL_FLOAT,
				GL_FALSE,
				sizeof(cookie::Vertex),
				(void *) offsetof(cookie::Vertex, normal));
		// vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(
				2, 2, GL_FLOAT, GL_FALSE, sizeof(cookie::Vertex),
				(void *) offsetof(cookie::Vertex, texCoords));

		glEnableVertexAttribArray(3);
		glVertexAttribIPointer(
				3,
				1,
				GL_INT,
				sizeof(cookie::Vertex),
				(void *) offsetof(cookie::Vertex, matrixOffset));
		EGLErrorHandler::checkOpenGLError();
		glBindVertexArray(0);
	}

	inline void EGLBufferStorage::setupMatricesBuffer(const std::vector<glm::mat4> &matrices) const {
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, sboMatrices);
		glBufferData(
				GL_SHADER_STORAGE_BUFFER,
				sizeof(glm::mat4) * matrices.size(),
				matrices.data(),
				GL_DYNAMIC_DRAW
		);
		GLErrorHandler::checkOpenGLError();
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}

	void EGLBufferStorage::setupMaterialBuffer(const cookie::MeshData &meshData) const {
		glBindBuffer(GL_UNIFORM_BUFFER, uboMaterial);
		glBufferData(
				GL_UNIFORM_BUFFER,
				sizeof(cookie::GPUMaterial),
				(void *) ((char *) meshData.material.get() + offsetof(cookie::Material, baseColor)),
				GL_STATIC_DRAW
		);
		EGLErrorHandler::checkOpenGLError();
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void EGLBufferStorage::bind() const {
		glBindVertexArray(vao);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, sboMatrices);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, sboMatrices);
		glBindBuffer(GL_UNIFORM_BUFFER, uboMaterial);
		GLint id;
		glGetIntegerv(GL_CURRENT_PROGRAM, &id);
		unsigned int matrices_index = glGetUniformBlockIndex(id, MATERIAL_UNIFORM_BLOCK.c_str());
		glUniformBlockBinding(id, matrices_index, 2);
		glBindBufferBase(GL_UNIFORM_BUFFER, 2, uboMaterial);
		GLErrorHandler::checkOpenGLError();
	}

	void EGLBufferStorage::unbind() const {
		glBindVertexArray(0);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		GLErrorHandler::checkOpenGLError();
	}
}

#endif