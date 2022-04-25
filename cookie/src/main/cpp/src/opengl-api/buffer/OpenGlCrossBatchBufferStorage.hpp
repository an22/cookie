//
// Created by Antiufieiev Michael on 21.10.2021.
//

#ifndef COOKIE_ENGINE_OPENGLCROSSBATCHBUFFERSTORAGE_HPP
#define COOKIE_ENGINE_OPENGLCROSSBATCHBUFFERSTORAGE_HPP

#include "CrossBatchBufferStorage.hpp"
#include "GLES3/gl3.h"

class OpenGLCrossBatchBufferStorage : public cookie::CrossBatchBufferStorage {
	GLuint uboMatrices{};

public:
	OpenGLCrossBatchBufferStorage();
	~OpenGLCrossBatchBufferStorage() override;

	void bind() override;
	void updateMatrices(const glm::mat4 &projection, const glm::mat4 &view) override;
};


#endif //COOKIE_ENGINE_OPENGLCROSSBATCHBUFFERSTORAGE_HPP
