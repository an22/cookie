//
// Created by Antiufieiev Michael on 21.10.2021.
//
#include "config.hpp"

#if COOKIE_EGL

#include <glm/gtc/type_ptr.hpp>
#include <EGLErrorHandler.hpp>
#include "EGLGlobalBufferStorage.hpp"

namespace cookie {

	void EGLGlobalBufferStorage::updateMatrices(
			const glm::mat4 &projection,
			const glm::mat4 &view
	) {
		glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
		glBufferSubData(
				GL_UNIFORM_BUFFER,
				sizeof(glm::mat4),
				sizeof(glm::mat4),
				glm::value_ptr(view));
		EGLErrorHandler::checkOpenGLError();
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	EGLGlobalBufferStorage::OpenGLGlobalBufferStorage() {
		glGenBuffers(1, &uboMatrices);
		glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
		glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);
		EGLErrorHandler::checkOpenGLError();
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void EGLGlobalBufferStorage::bind() {
		GLint id;
		glGetIntegerv(GL_CURRENT_PROGRAM, &id);
		unsigned int matrices_index = glGetUniformBlockIndex(id, "Matrices");
		glUniformBlockBinding(id, matrices_index, 0);
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, uboMatrices);
		EGLErrorHandler::checkOpenGLError();
	}

	void EGLGlobalBufferStorage::createFaceBuffer() {
		glGenBuffers(1, &ssboFaces);
	}

	void EGLGlobalBufferStorage::createLightBuffer() {
		glGenBuffers(1, &ssboLights);
	}

	void EGLGlobalBufferStorage::createFaceIndexHashesBuffer() {
		glGenBuffers(1, &ssboFaceIndexHashes);
	}

	void EGLGlobalBufferStorage::createFaceIndexesBuffer() {
		glGenBuffers(1, &ssboFaceIndexes);
	}

	void EGLGlobalBufferStorage::createMaterialsBuffer() {
		glGenBuffers(1, &ssboMaterials);
	}

	EGLGlobalBufferStorage::~OpenGLGlobalBufferStorage() {
		glDeleteBuffers(1, &uboMatrices);
		if (ssboFaces != -1) glDeleteBuffers(1, &ssboFaces);
		if (ssboLights != -1) glDeleteBuffers(1, &ssboLights);
		if (ssboFaceIndexes != -1) glDeleteBuffers(1, &ssboFaceIndexes);
		if (ssboFaceIndexHashes != -1) glDeleteBuffers(1, &ssboFaceIndexHashes);
		if (ssboMaterials != -1) glDeleteBuffers(1, &ssboMaterials);
	}
}

#endif
