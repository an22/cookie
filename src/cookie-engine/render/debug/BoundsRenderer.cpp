//
// Created by Michael on 6/15/2022.
//

#include "BoundsRenderer.h"
#include "BufferStorage.hpp"
#include "SceneObject.hpp"
#include "Material.h"
#include "DrawUtils.h"
#include "MeshComponent.hpp"
#include "PointsData.h"
#include <iterator>

namespace cookie {

	inline void initBatchConfig(MultiDrawConfig &config, size_t size) {
		config.meshCount = size;
		config.startOffset.reserve(size);
		config.baseVertexOffset.reserve(size);
		config.indicesSize.reserve(size);
	}

	inline void combinePointsData(
			const std::list<std::shared_ptr<SceneObject>> &sceneObjects,
			std::vector<glm::vec4> &vertices,
			std::vector<uint32_t> &indices,
			std::vector<glm::mat4> &matrices,
			MultiDrawConfig &config
	) {
		int32_t vertexOffset = 0;
		int32_t indexOffset = 0;
		size_t i = 0;
		std::vector<uint32_t> _indices(Bounds::indices, Bounds::indices + sizeof(Bounds::indices) / sizeof(uint32_t));
		for (auto &sceneObject: sceneObjects) {
			const auto &mesh = sceneObject->getComponent<MeshComponent>();
			if (mesh == nullptr) { continue; }
			const auto &bounds = mesh->getTransformedBounds();

			std::copy(bounds.points.begin(), bounds.points.end(), std::back_inserter(vertices));
			std::copy(_indices.begin(), _indices.end(), std::back_inserter(indices));

			config.startOffset.emplace_back(static_cast<int32_t>(indexOffset * sizeof(uint32_t)));
			config.indicesSize.emplace_back(static_cast<int32_t>(_indices.size()));
			config.baseVertexOffset.emplace_back(vertexOffset);
			i++;
			indexOffset += static_cast<int32_t>(_indices.size());
			vertexOffset += static_cast<int32_t>(bounds.points.size());
		}
	}

	BoundsRenderer::BoundsRenderer(const std::shared_ptr<Material> &material) : SubRenderable(material) {}

	void BoundsRenderer::saveToGPU(const std::list<std::shared_ptr<SceneObject>> &sceneObjects) {
		size_t size = 0;
		for (auto &obj: sceneObjects) {
			if (obj->getComponent<MeshComponent>() != nullptr) { size++; }
		}
		size_t vertexSize = 8 * size;
		size_t indexSize = 14 * size;
		std::vector<glm::vec4> vertices;
		std::vector<uint32_t> indices;
		std::vector<glm::mat4> matrices;

		initBatchConfig(config, size);

		vertices.reserve(vertexSize);
		indices.reserve(indexSize);

		combinePointsData(sceneObjects, vertices, indices, matrices, config);

		PointsData pointsData(vertices, indices);
		bufferStorage->saveToBuffer(pointsData, matrices);
	}

	void BoundsRenderer::render(const DrawUtils &drawUtils) {
		material->onPreDraw();
		bufferStorage->bind();
		drawUtils.setPolygonMode(PolyMode::LINE);
		drawUtils.drawMultiElementsWithIndexOffset(
				DrawMode::TRIANGLES,
				config.meshCount,
				config.startOffset.data(),
				config.indicesSize.data(),
				config.baseVertexOffset.data()
		);
		drawUtils.setPolygonMode(PolyMode::FILL);
		bufferStorage->unbind();
		material->onPostDraw();
	}
}
