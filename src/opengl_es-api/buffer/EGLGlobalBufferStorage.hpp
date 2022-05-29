//
// Created by Antiufieiev Michael on 21.10.2021.
//

#ifndef COOKIE_ENGINE_EGLCROSSBATCHBUFFERSTORAGE_HPP
#define COOKIE_ENGINE_EGLCROSSBATCHBUFFERSTORAGE_HPP

#if COOKIE_EGL

#include "GlobalBufferStorage.hpp"
#include "GLES3/gl32.h"

namespace cookie {
	class EGLGlobalBufferStorage : public cookie::GlobalBufferStorage {
		GLuint uboMatrices = -1;
		GLuint ssboFaces = -1;
		GLuint ssboMaterials = -1;
		GLuint ssboLights = -1;
		GLuint ssboFaceIndexHashes = -1;
		GLuint ssboFaceIndexes = -1;
	public:
		EGLGlobalBufferStorage();
		~EGLGlobalBufferStorage() override;
		void bind() override;
		void createFaceBuffer() override;
		void createLightBuffer() override;
		void createFaceIndexHashesBuffer() override;
		void createFaceIndexesBuffer() override;
		void createMaterialsBuffer() override;
		void updateMatrices(const glm::mat4 &projection, const glm::mat4 &view) override;
	};
}

#endif
#endif //COOKIE_ENGINE_EGLCROSSBATCHBUFFERSTORAGE_HPP
