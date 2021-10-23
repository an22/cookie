//
// Created by Antiufieiev Michael on 10.10.2021.
//

#include "Batch.hpp"
#include "Mesh.hpp"
#include "CookieFactory.hpp"
#include "PlatformSpecificBufferData.h"
#include <iostream>

void cookie::Batch::addObject(std::shared_ptr<SceneObject> sceneObject) {
	sceneObjects.push_back(std::move(sceneObject));
}

void cookie::Batch::removeObject(const std::shared_ptr<SceneObject> &sceneObject) {
	const auto &it = std::find(sceneObjects.begin(), sceneObjects.end(), sceneObject);
	sceneObjects.erase(it);
}

cookie::Batch::Batch(const std::shared_ptr<Material> &material) : bufferStorage(CookieFactory::provideBufferStorage()),
																  material(std::shared_ptr(material)),
																  sceneObjects{} {
}

void cookie::Batch::syncWithVideoBuffer() {
	unsigned int vertexSize = 0;
	unsigned int indexSize = 0;
	for (auto &sceneObject: sceneObjects) {
		const auto &mesh = sceneObject->getComponent<Mesh>();
		vertexSize += mesh->getVertices().size();
		indexSize += mesh->getIndices().size();
	}
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<glm::mat4> matrices;
	config.meshCount = sceneObjects.size();
	config.baseVertexOffset = new int32_t[sceneObjects.size()];
	config.indicesSize = new int32_t[sceneObjects.size()];
	vertices.reserve(vertexSize);
	indices.reserve(indexSize);
	matrices.reserve(sceneObjects.size());
	std::shared_ptr<Material> empty(nullptr);

	int32_t vertexOffset = 0;
	int32_t indexOffset = 0;
	int32_t matrixOffset = 0;
	int32_t i = 0;
	for (auto &sceneObject: sceneObjects) {
		const auto &mesh = sceneObject->getComponent<Mesh>();
		const auto &meshIndices = mesh->getIndices();
		auto &meshVertices = mesh->getVertices();
		vertices.insert(vertices.begin() + vertexOffset, meshVertices.begin(), meshVertices.end());
		indices.insert(indices.begin() + indexOffset, meshIndices.begin(), meshIndices.end());
		matrices.insert(matrices.begin() + i, sceneObject->getModelMat());
		for (auto &vertex: meshVertices) {
			vertex.matrixOffset = matrixOffset;
		}
		config.indicesSize[i] = meshIndices.size();
		config.baseVertexOffset[i] = vertexOffset;
		vertexOffset += static_cast<int32_t>(meshVertices.size());
		indexOffset += static_cast<int32_t>(meshIndices.size());
		matrixOffset += 4;
		i++;
	}
	for( int j = 0; j < i; j++) {
		std::cout << config.indicesSize[j] << " ";
	}
	std::cout << std::endl;
	for( int j = 0; j < i; j++) {
		std::cout << config.baseVertexOffset[j] << " ";
	}
	std::cout << std::endl;
	MeshData meshData("", vertices, indices, empty);
	bufferStorage->saveToBuffer(
			meshData,
			matrices,
			CookieFactory::provideBufferData(cookie::BufferType::VERTEX_BUFFER)
	);
}

void cookie::Batch::draw(const DrawUtils &drawUtils) {
	bufferStorage->bind();
	material->onPreDraw();
	drawUtils.drawMultiElementsWithIndexOffset(
			config.meshCount,
			config.indicesSize,
			config.baseVertexOffset
	);
}
