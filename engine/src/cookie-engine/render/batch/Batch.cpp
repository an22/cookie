//
// Created by Antiufieiev Michael on 10.10.2021.
//

#include <iterator>
#include <algorithm>
#include <glm/glm.hpp>
#include "Batch.hpp"
#include "SceneObject.hpp"
#include "MeshComponent.hpp"
#include "MeshStruct.h"
#include "Material.h"
#include "TextureProcessor.hpp"
#include "BufferStorage.hpp"
#include "Shader.hpp"
#include "DrawUtils.h"

namespace cookie {

	inline void initBatchConfig(MultiDrawConfig &config, size_t size) {
		config.meshCount = size;
		config.startOffset.reserve(size);
		config.baseVertexOffset.reserve(size);
		config.indicesSize.reserve(size);
	}

	inline void calculateVertexAndIndexSize(
			const std::list<std::shared_ptr<SceneObject>> &sceneObjects,
			uint32_t &vertexCount,
			uint32_t &indexCount
	) {
		vertexCount = 0;
		indexCount = 0;
		for (auto &sceneObject: sceneObjects) {
			const auto &mesh = sceneObject->getComponent<MeshComponent>();
			vertexCount += mesh->getVertices().size();
			indexCount += mesh->getIndices().size();
		}
	}

	inline void combineMeshData(
			const std::list<std::shared_ptr<SceneObject>> &sceneObjects,
			std::vector<Vertex> &vertices,
			std::vector<uint32_t> &indices,
			std::vector<glm::mat4> &matrices,
			MultiDrawConfig &config
	) {
		uint32_t vertexOffset = 0;
		uint32_t indexOffset = 0;
		int32_t i = 0;
		for (auto &sceneObject: sceneObjects) {
			const auto &mesh = sceneObject->getComponent<MeshComponent>();
			const auto &meshIndices = mesh->getIndices();
			auto &meshVertices = mesh->getVertices();

			for (auto &vertex: meshVertices) {
				vertex.matrixOffset = i;
			}
			std::copy(meshVertices.begin(), meshVertices.end(), std::back_inserter(vertices));
			std::copy(meshIndices.begin(), meshIndices.end(), std::back_inserter(indices));

			matrices.emplace_back(sceneObject->getModelMat());

			config.startOffset.emplace_back(static_cast<int32_t>(indexOffset * sizeof(uint32_t)));
			config.indicesSize.emplace_back(static_cast<int32_t>(meshIndices.size()));
			config.baseVertexOffset.emplace_back(static_cast<int32_t>(vertexOffset));

			vertexOffset += meshVertices.size();
			indexOffset += meshIndices.size();
			i++;
		}
	}

	Batch::Batch(const std::shared_ptr<Material> &material) : Renderable(material),
															  sceneObjects{} {
	}

	Batch::~Batch() = default;

	void Batch::addObject(std::shared_ptr<SceneObject> sceneObject) {
		sceneObjects.emplace_back(std::move(sceneObject));
	}

	void Batch::removeObject(const std::shared_ptr<SceneObject> &sceneObject) {
		const auto &it = std::find(sceneObjects.begin(), sceneObjects.end(), sceneObject);
		sceneObjects.erase(it);
	}

	void Batch::saveToGPU() {
		uint32_t vertexSize;
		uint32_t indexSize;
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		std::vector<glm::mat4> matrices;

		initBatchConfig(config, sceneObjects.size());
		calculateVertexAndIndexSize(sceneObjects, vertexSize, indexSize);

		vertices.reserve(vertexSize);
		indices.reserve(indexSize);
		matrices.reserve(sceneObjects.size());

		combineMeshData(sceneObjects, vertices, indices, matrices, config);

		MeshData meshData("", vertices, indices, material);
		bufferStorage->saveToBuffer(meshData, matrices);
	}

	void Batch::render(const DrawUtils &drawUtils) {
		material->onPreDraw();
		bufferStorage->bind();
		drawUtils.drawMultiElementsWithIndexOffset(
				DrawMode::TRIANGLES,
				config.meshCount,
				config.startOffset.data(),
				config.indicesSize.data(),
				config.baseVertexOffset.data()
		);
		bufferStorage->unbind();
		material->onPostDraw();
	}

	Batch::Batch(Batch &&other) noexcept: Renderable(std::move(other)) {
	}
}
