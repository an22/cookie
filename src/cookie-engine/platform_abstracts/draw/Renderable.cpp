//
// Created by Michael on 6/13/2022.
//

#include "Renderable.hpp"

#include <utility>
#include "BufferStorage.hpp"
#include "CookieFactory.hpp"
#include "Material.h"

namespace cookie {

	void Renderable::saveToGPUInternal(const MeshData &meshData, const std::vector<glm::mat4> &matrices) {
		material->enableShader();
		bufferStorage->saveToBuffer(meshData, matrices);
		material->disableShader();
	}

	void Renderable::render(const DrawUtils &drawUtils) {
		bufferStorage->bind();
		material->onPreDraw();
		draw(drawUtils);
		material->onPostDraw();
		bufferStorage->unbind();
	}

	Renderable::Renderable(std::shared_ptr<Material> material) : bufferStorage(CookieFactory::provideBufferStorage()), material(std::move(material)) {}

	Renderable::~Renderable() = default;
}
