//
//  OpenGLBufferStorage.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//
#include "config.hpp"

#if COOKIE_OPENGL

#include "CookieConstants.hpp"
#include "Material.h"
#include "OpenGLBufferStorage.hpp"
#include "GLErrorHandler.hpp"
#include "MeshStruct.h"
#include "PointsData.h"

namespace cookie {
	OpenGLBufferStorage::OpenGLBufferStorage() : cookie::BufferStorage() {
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vboVertex);
		glGenBuffers(1, &uboMaterial);
		glGenBuffers(1, &vboIndex);
		glGenBuffers(1, &sboMatrices);
	}

	OpenGLBufferStorage::~OpenGLBufferStorage() {
		glDeleteBuffers(1, &vboVertex);
		glDeleteBuffers(1, &uboMaterial);
		glDeleteBuffers(1, &vboIndex);
		glDeleteBuffers(1, &sboMatrices);
		glDeleteVertexArrays(1, &vao);
	}

	void OpenGLBufferStorage::saveToBuffer(
			const cookie::MeshData &meshData,
			const std::vector<glm::mat4> &matrices
	) const {
		setupVertexElementBuffer(meshData);
		setupMaterialBuffer(meshData);
		setupMatricesBuffer(matrices);
	}

	void OpenGLBufferStorage::saveToBuffer(const PointsData &pointsData, const std::vector<glm::mat4> &matrices) const {
		setupPointElementBuffer(pointsData);
		setupMatricesBuffer(matrices);
	}

	inline void OpenGLBufferStorage::setupVertexElementBuffer(const cookie::MeshData &meshData) const {
		glBindVertexArray(vao);
		fillVertexBuffer(meshData.vertices);
		fillElementsBuffer(meshData.indices);
		setVertexAttributePointers();
		GLErrorHandler::checkOpenGLError();
		glBindVertexArray(0);
	}

	void OpenGLBufferStorage::setupPointElementBuffer(const PointsData &pointsData) const {
		glBindVertexArray(vao);
		fillPointsBuffer(pointsData.points);
		fillElementsBuffer(pointsData.indices);
		setPointAttributePointers();
		GLErrorHandler::checkOpenGLError();
		glBindVertexArray(0);
	}

	inline void OpenGLBufferStorage::setVertexAttributePointers() {
		// vertex coords
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) nullptr);
		// vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, normal));
		// vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, texCoords));
		// matrix index
		glEnableVertexAttribArray(3);
		glVertexAttribIPointer(3, 1, GL_INT, sizeof(Vertex), (void *) offsetof(Vertex, matrixOffset));
	}

	void OpenGLBufferStorage::setPointAttributePointers() {
		// points coords
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void *) nullptr);
	}

	inline void OpenGLBufferStorage::fillElementsBuffer(const std::vector<uint32_t> &indices) const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndex);
		glBufferData(
				GL_ELEMENT_ARRAY_BUFFER,
				indices.size() * sizeof(uint32_t),
				indices.data(),
				GL_STATIC_DRAW
		);
	}

	inline void OpenGLBufferStorage::fillVertexBuffer(const std::vector<Vertex> &vertices) const {
		glBindBuffer(GL_ARRAY_BUFFER, vboVertex);
		glBufferData(
				GL_ARRAY_BUFFER,
				sizeof(Vertex) * vertices.size(),
				vertices.data(),
				GL_STATIC_DRAW
		);
	}

	inline void OpenGLBufferStorage::fillPointsBuffer(const std::vector<glm::vec4> &vertices) const {
		glBindBuffer(GL_ARRAY_BUFFER, vboVertex);
		glBufferData(
				GL_ARRAY_BUFFER,
				sizeof(glm::vec4) * vertices.size(),
				vertices.data(),
				GL_STATIC_DRAW
		);
	}

	inline void OpenGLBufferStorage::setupMatricesBuffer(const std::vector<glm::mat4> &matrices) const {
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
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, sboMatrices);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, sboMatrices);
		glBindBuffer(GL_UNIFORM_BUFFER, uboMaterial);
//		GLint id;
//		glGetIntegerv(GL_CURRENT_PROGRAM, &id);
//		unsigned int matrices_index = glGetUniformBlockIndex(id, MATERIAL_UNIFORM_BLOCK.c_str());
//		glUniformBlockBinding(id, matrices_index, 2);
		glBindBufferBase(GL_UNIFORM_BUFFER, 2, uboMaterial);
		GLErrorHandler::checkOpenGLError();
	}

	void OpenGLBufferStorage::unbind() const {
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		glBindVertexArray(0);
		GLErrorHandler::checkOpenGLError();
	}
}
#endif
