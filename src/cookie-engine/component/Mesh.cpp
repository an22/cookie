//
//  Mesh.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 06.08.2021.
//

#include "Mesh.hpp"
#include "CookieFactory.hpp"
#include "DrawUtils.h"
#include "AssetImporter.hpp"
#include <utility>

namespace cookie {

	Mesh::Mesh(std::unique_ptr<MeshData> meshData) : meshData(std::move(meshData)),
													 bufferStorage(CookieFactory::provideBufferStorage()) {
		std::unique_ptr<PlatformSpecificBufferData> data = CookieFactory::provideBufferData(BufferType::VERTEX_BUFFER);
		bufferStorage->saveToBuffer(*this->meshData, std::move(data));
	}

	Mesh::Mesh(
			const std::vector<Vertex> &vertices,
			const std::vector<unsigned int> &indices,
			const std::vector<Texture> &textures
	) : meshData(std::make_unique<MeshData>(vertices, indices, textures)),
		bufferStorage(CookieFactory::provideBufferStorage()) {
		std::unique_ptr<PlatformSpecificBufferData> data = CookieFactory::provideBufferData(BufferType::VERTEX_BUFFER);
		bufferStorage->saveToBuffer(*this->meshData, std::move(data));
	}

	Mesh::Mesh(const std::string &path) : bufferStorage(CookieFactory::provideBufferStorage()) {
		meshData = std::move(AssetImporter::importMesh(path)[0]);//TODO change
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
	}

	void Mesh::onPreDraw(Material &material) {
		material.onPreDraw();
		bufferStorage->bind();
	}
}
