//
// Created by Michael on 6/13/2022.
//

#include "Renderable.hpp"
#include "BufferStorage.hpp"
#include "CookieFactory.hpp"

namespace cookie {

	void Renderable::saveToGPUInternal(const MeshData &meshData, const std::vector<glm::mat4> &matrices) {
		bufferStorage->saveToBuffer(meshData, matrices);
	}

	void Renderable::render(const DrawUtils &drawUtils) {
		bufferStorage->bind();
		draw(drawUtils);
		bufferStorage->unbind();
	}

	Renderable::Renderable() : bufferStorage(CookieFactory::provideBufferStorage()) {}

	Renderable::~Renderable() = default;
}
