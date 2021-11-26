//
// Created by Antiufieiev Michael on 10.10.2021.
//

#include "Batch.hpp"
#include "Mesh.hpp"
#include "CookieFactory.hpp"
#include "PlatformSpecificBufferData.h"
#include <iostream>
#include <iterator>
#include <glm/gtx/string_cast.hpp>
#include <GLErrorHandler.hpp>

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
	config.startOffset = new unsigned int [sceneObjects.size()];
	config.baseVertexOffset = new unsigned int[sceneObjects.size()];
	config.indicesSize = new unsigned int[sceneObjects.size()];
	vertices.reserve(vertexSize);
	indices.reserve(indexSize);
	matrices.reserve(sceneObjects.size());
	std::shared_ptr<Material> empty(nullptr);

	unsigned int vertexOffset = 0;
	unsigned int indexOffset = 0;
	unsigned int matrixOffset = 0;
	int32_t i = 0;
	for (auto &sceneObject: sceneObjects) {
		const auto &mesh = sceneObject->getComponent<Mesh>();
		const auto &meshIndices = mesh->getIndices();
		auto &meshVertices = mesh->getVertices();
		for (auto &vertex: meshVertices) {
			vertex.matrixOffset = matrixOffset;
		}
		std::copy (meshVertices.begin(), meshVertices.end(), std::back_inserter(vertices));
		std::copy (meshIndices.begin(), meshIndices.end(), std::back_inserter(indices));
		matrices.emplace_back(sceneObject->getModelMat());
		config.startOffset[i] = indexOffset * sizeof(unsigned int);
		config.indicesSize[i] = meshIndices.size();
		config.baseVertexOffset[i] = vertexOffset;
		vertexOffset += meshVertices.size();
		indexOffset += meshIndices.size();
		matrixOffset += 1;
		i++;
	}
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
			config.startOffset,
			config.indicesSize,
			config.baseVertexOffset
	);
}