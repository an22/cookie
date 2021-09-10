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
													 bufferStorage(CookieFactory::provideBufferStorage()),
													 textureProcessor(CookieFactory::provideTextureProcessor()) {
		std::unique_ptr<PlatformSpecificBufferData> data = CookieFactory::provideBufferData(BufferType::VERTEX_BUFFER);
		bufferStorage->saveToBuffer(*this->meshData, std::move(data));
	}

	Mesh::Mesh(
			std::vector<Vertex> &vertices,
			std::vector<unsigned int> &indices,
			std::vector<Texture> &textures
	) : meshData(
			std::make_unique<MeshData>(
					std::move(vertices),
					std::move(indices),
					std::move(textures),
					glm::mat4{1}
			)
	),
		bufferStorage(CookieFactory::provideBufferStorage()),
		textureProcessor(CookieFactory::provideTextureProcessor()) {
		std::unique_ptr<PlatformSpecificBufferData> data = CookieFactory::provideBufferData(BufferType::VERTEX_BUFFER);
		bufferStorage->saveToBuffer(*this->meshData, std::move(data));
	}

	const std::vector<Vertex> &Mesh::getVertices() const {
		return meshData->vertices;
	}

	const std::vector<uint32_t> &Mesh::getIndices() const {
		return meshData->indices;
	}

	const std::vector<Texture> &Mesh::getTextures() const {
		return meshData->textures;
	}

	void Mesh::onPreDraw(Shader &shader) {
		shader.use();
		bufferStorage->bind();
		textureProcessor->bindTexturesToShader(meshData->textures, shader);
	}

	void Mesh::onPreDraw(Material &material) {
		material.onPreDraw();
		bufferStorage->bind();
		textureProcessor->bindTexturesToShader(meshData->textures, material.getShader());
	}
}
