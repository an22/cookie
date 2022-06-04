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
#include "Bounds.hpp"
#include "TextureProcessor.hpp"

namespace cookie {

	class MeshComponent : public Component {
	private:
		std::unique_ptr<TextureProcessor> textureProcessor;
		// mesh data
		std::unique_ptr<MeshData> meshData;
		Bounds bounds;
	public:
		[[nodiscard]] const Bounds &getBounds() const;
		[[nodiscard]] std::vector<Vertex> &getVertices() const;
		[[nodiscard]] const std::vector<unsigned int> &getIndices() const;
		[[nodiscard]] std::shared_ptr<Material> getMaterial() const;
		MeshComponent(std::unique_ptr<MeshData> meshData, const Bounds& _bounds);
		MeshComponent();
		~MeshComponent() override = default;
	};
}

#endif /* Mesh_hpp */
