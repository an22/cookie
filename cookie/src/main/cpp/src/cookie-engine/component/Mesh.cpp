//
//  Mesh.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 06.08.2021.
//

#include "Mesh.hpp"
#include "CookieFactory.hpp"
#include "DrawUtils.h"
#include <utility>

namespace cookie {

	Mesh::Mesh(std::unique_ptr<MeshData> meshData) : meshData(std::move(meshData)),
													 textureProcessor(CookieFactory::provideTextureProcessor()) {
		std::unique_ptr<PlatformSpecificBufferData> data = CookieFactory::provideBufferData(BufferType::VERTEX_BUFFER);
	}

	Mesh::Mesh() : meshData(std::make_unique<MeshData>()),
		textureProcessor(CookieFactory::provideTextureProcessor()) {
		std::unique_ptr<PlatformSpecificBufferData> data = CookieFactory::provideBufferData(BufferType::VERTEX_BUFFER);
	}

	std::vector<Vertex> &Mesh::getVertices() const {
		return meshData->vertices;
	}

	const std::vector<uint32_t> &Mesh::getIndices() const {
		return meshData->indices;
	}

	void Mesh::onPreDraw(Shader &shader) {
		shader.use();

	}

	void Mesh::onPreDraw(Material &material) {
		material.onPreDraw();

	}

	std::shared_ptr<Material> Mesh::getMaterial() const {
		return meshData->material;
	}
}
