//
//  Mesh.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 28.07.2021.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <memory>
#include "Component.hpp"
#include "Shader.hpp"
#include "Material.h"
#include "MeshStruct.h"

namespace cookie {

	class Mesh : public Component {
	private:
		std::unique_ptr<BufferStorage> bufferStorage;
		// mesh data
		std::unique_ptr<MeshData> meshData;
	public:
		[[nodiscard]] const std::vector<Vertex> &getVertices() const;
		[[nodiscard]] const std::vector<unsigned int> &getIndices() const;
		[[nodiscard]] const std::vector<Texture> &getTextures() const;

		void onPreDraw(Shader &shader);
		void onPreDraw(Material &material);
		explicit Mesh(std::unique_ptr<MeshData> meshData);
		explicit Mesh(const std::string &path);
		Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices,
			 const std::vector<Texture> &textures);
		~Mesh() override = default;
	};
}

#endif /* Mesh_hpp */
