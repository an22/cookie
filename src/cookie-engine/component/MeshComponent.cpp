//
//  MeshComponent.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 06.08.2021.
//

#include "MeshComponent.hpp"
#include "CookieFactory.hpp"
#include "DrawUtils.h"
#include <utility>

namespace cookie {

	MeshComponent::MeshComponent(
			std::unique_ptr<MeshData> meshData,
			const Bounds &_bounds
	) : meshData(std::move(meshData)),
		textureProcessor(CookieFactory::provideTextureProcessor()),
		bounds(_bounds) {
	}

	MeshComponent::MeshComponent() : meshData(std::make_unique<MeshData>()),
									 textureProcessor(CookieFactory::provideTextureProcessor()),
									 bounds() {
	}

	std::vector<Vertex> &MeshComponent::getVertices() const {
		return meshData->vertices;
	}

	const std::vector<uint32_t> &MeshComponent::getIndices() const {
		return meshData->indices;
	}

	std::shared_ptr<Material> MeshComponent::getMaterial() const {
		return meshData->material;
	}

	const Bounds &MeshComponent::getBounds() const {
		return bounds;
	}
}
