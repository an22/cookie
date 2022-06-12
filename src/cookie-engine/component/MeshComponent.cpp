//
//  MeshComponent.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 06.08.2021.
//

#include <utility>
#include "CookieFactory.hpp"
#include "SceneObject.hpp"
#include "Transformation.hpp"
#include "MeshComponent.hpp"
#include "MeshStruct.h"
#include "TextureProcessor.hpp"
#include "DrawUtils.h"

namespace cookie {

	MeshComponent::MeshComponent(
			const std::shared_ptr<SceneObject> &objPtr,
			std::unique_ptr<MeshData> meshData,
			const Bounds &_bounds
	) : Component(objPtr),
		meshData(std::move(meshData)),
		textureProcessor(CookieFactory::provideTextureProcessor()),
		staticBounds(_bounds),
		transformedBounds(_bounds) {
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
		return staticBounds;
	}

	void MeshComponent::updateMatrix(const glm::mat4 &transformation) {
		transformedBounds = staticBounds.transform(transformation);
	}

	const Bounds &MeshComponent::getTransformedBounds() {
		auto& transformation = owner.lock()->getTransformation();
		if(transformation->isChanged()) {
			updateMatrix(transformation->getGlobalTransformationMatrix());
		}
		return transformedBounds;
	}

}
