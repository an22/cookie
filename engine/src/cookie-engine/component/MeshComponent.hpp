//
//  MeshComponent.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 28.07.2021.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <vector>
#include <memory>
#include <glm/mat4x4.hpp>
#include "Bounds.hpp"
#include "Component.hpp"

namespace cookie {

	struct MeshData;
	struct Vertex;
	class SceneObject;
	class TextureProcessor;
	class Material;

	class MeshComponent : public Component {
	private:
		std::unique_ptr<TextureProcessor> textureProcessor;
		std::unique_ptr<MeshData> meshData;

		Bounds staticBounds;
		Bounds transformedBounds;
	public:
		MeshComponent(
				const std::shared_ptr<SceneObject> &objPtr,
				std::unique_ptr<MeshData> meshData,
				const Bounds &_bounds
		);
		~MeshComponent() override = default;
		[[nodiscard]] const Bounds &getBounds() const;
		[[nodiscard]] const Bounds &getTransformedBounds();
		[[nodiscard]] std::vector<Vertex> &getVertices() const;
		[[nodiscard]] const std::vector<unsigned int> &getIndices() const;
		[[nodiscard]] const std::shared_ptr<Material> &getMaterial() const;
		void updateMatrix(const glm::mat4 &transformation);
	};
}

#endif /* Mesh_hpp */
