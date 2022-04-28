//
//  Mesh.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 28.07.2021.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <vector>
#include <memory>
#include "TextureProcessor.hpp"

namespace cookie {

	class Mesh : public Component {
	private:
		std::unique_ptr<TextureProcessor> textureProcessor;
		// mesh data
		std::unique_ptr<MeshData> meshData;
	public:
		[[nodiscard]] std::vector<Vertex> &getVertices() const;
		[[nodiscard]] const std::vector<unsigned int> &getIndices() const;
		[[nodiscard]] std::shared_ptr<Material> getMaterial() const;
		explicit Mesh(std::unique_ptr<MeshData> meshData);
		Mesh();
		~Mesh() override = default;
	};
}

#endif /* Mesh_hpp */
