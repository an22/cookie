//
// Created by Antiufieiev Michael on 21.10.2021.
//

#ifndef COOKIE_ENGINE_OPENGLCROSSBATCHBUFFERSTORAGE_HPP
#define COOKIE_ENGINE_OPENGLCROSSBATCHBUFFERSTORAGE_HPP

#include "CrossBatchBufferStorage.hpp"
#include "GL/glew.h"

namespace cookie {
	class OpenGLCrossBatchBufferStorage : public CrossBatchBufferStorage {
		GLuint uboMatrices{};

	public:
		OpenGLCrossBatchBufferStorage();
		~OpenGLCrossBatchBufferStorage() override;
		void bind() override;
		void updateMatrices(const glm::mat4 &projection, const glm::mat4 &view) override;
	};
}


#endif //COOKIE_ENGINE_OPENGLCROSSBATCHBUFFERSTORAGE_HPP
