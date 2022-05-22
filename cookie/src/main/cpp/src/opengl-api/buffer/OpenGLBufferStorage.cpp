//
//  OpenGLBufferStorage.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include <EGL/egl.h>
#include <GLES3/gl32.h>
#include "OpenGLBufferStorage.hpp"
#include "GLErrorHandler.hpp"

namespace cookie {
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
		GLErrorHandler::checkOpenGLError();
		glBindVertexArray(0);
	}

	inline void OpenGLBufferStorage::setupMatricesBuffer(const std::vector<glm::mat4> &matrices) const {
		glBindBuffer(GL_TEXTURE_BUFFER, tboMatrices);
		glBufferData(
				GL_TEXTURE_BUFFER,
				sizeof(glm::mat4) * matrices.size(),
				matrices.data(),
				GL_STATIC_DRAW
		);
		glBindTexture(GL_TEXTURE_BUFFER, texMatrices);
		glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, tboMatrices);
		GLErrorHandler::checkOpenGLError();
		glBindBuffer(GL_TEXTURE_BUFFER, 0);
	}

	void OpenGLBufferStorage::setupMaterialBuffer(const cookie::MeshData &meshData) const {
		glBindBuffer(GL_UNIFORM_BUFFER, uboMaterial);
		glBufferData(
				GL_UNIFORM_BUFFER,
				sizeof(cookie::GPUMaterial),
				(void *) ((char *) meshData.material.get() + offsetof(cookie::Material, baseColor)),
				GL_STATIC_DRAW
		);
		GLErrorHandler::checkOpenGLError();
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void OpenGLBufferStorage::bind() const {
		glBindVertexArray(vao);
		glBindBuffer(GL_TEXTURE_BUFFER, tboMatrices);
		glBindTexture(GL_TEXTURE_BUFFER, texMatrices);
		glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, tboMatrices);
		glBindBuffer(GL_UNIFORM_BUFFER, uboMaterial);
		GLint id;
		glGetIntegerv(GL_CURRENT_PROGRAM, &id);
		unsigned int matrices_index = glGetUniformBlockIndex(id, "Material");
		glUniformBlockBinding(id, matrices_index, 1);
		glBindBufferBase(GL_UNIFORM_BUFFER, 1, uboMaterial);
		GLErrorHandler::checkOpenGLError();
	}

	void OpenGLBufferStorage::unbind() const {
		glBindVertexArray(0);
		glBindBuffer(GL_TEXTURE_BUFFER, 0);
		glBindTexture(GL_TEXTURE_BUFFER, 0);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		GLErrorHandler::checkOpenGLError();
	}
}
