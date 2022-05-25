//
// Created by Antiufieiev Michael on 10.10.2021.
//

#include <iostream>
#include <iterator>
#include "Batch.hpp"
#include "Mesh.hpp"
#include "CookieFactory.hpp"
#include "PlatformSpecificBufferData.h"

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
	uint32_t vertexSize;
	uint32_t indexSize;
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	std::vector<glm::mat4> matrices;

	initBatchConfig();
	calculateVertexAndIndexSize(vertexSize, indexSize);

	vertices.reserve(vertexSize);
	indices.reserve(indexSize);
	matrices.reserve(sceneObjects.size());

	combineMeshData(vertices, indices, matrices);

	MeshData meshData("", vertices, indices, material);
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
			config.startOffset.data(),
			config.indicesSize.data(),
			config.baseVertexOffset.data()
	);
    bufferStorage->unbind();
}

void cookie::Batch::combineMeshData(std::vector<Vertex> &vertices, std::vector<uint32_t> &indices, std::vector<glm::mat4> &matrices) {
	uint32_t vertexOffset = 0;
	uint32_t indexOffset = 0;
	int32_t i = 0;
	for (auto &sceneObject: sceneObjects) {
		const auto &mesh = sceneObject->getComponent<Mesh>();
		const auto &meshIndices = mesh->getIndices();
		auto &meshVertices = mesh->getVertices();

		for (auto &vertex: meshVertices) {
			vertex.matrixOffset = i;
		}
		std::copy (meshVertices.begin(), meshVertices.end(), std::back_inserter(vertices));
		std::copy (meshIndices.begin(), meshIndices.end(), std::back_inserter(indices));

		matrices.emplace_back(sceneObject->getModelMat());

		config.startOffset.emplace_back(static_cast<int32_t>(indexOffset * sizeof(uint32_t)));
		config.indicesSize.emplace_back(static_cast<int32_t>(meshIndices.size()));
		config.baseVertexOffset.emplace_back(static_cast<int32_t>(vertexOffset));

		vertexOffset += meshVertices.size();
		indexOffset += meshIndices.size();
		i++;
	}
}

void cookie::Batch::calculateVertexAndIndexSize(uint32_t &vertexCount, uint32_t &indexCount) {
	vertexCount = 0;
	indexCount = 0;
	for (auto &sceneObject: sceneObjects) {
		const auto &mesh = sceneObject->getComponent<Mesh>();
		vertexCount += mesh->getVertices().size();
		indexCount += mesh->getIndices().size();
	}
}

void cookie::Batch::initBatchConfig() {
	config.meshCount = sceneObjects.size();
	config.startOffset.reserve(sceneObjects.size());
	config.baseVertexOffset.reserve(sceneObjects.size());
	config.indicesSize.reserve(sceneObjects.size());
}