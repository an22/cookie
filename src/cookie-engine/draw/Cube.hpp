//
//  Cube.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 06.07.2021.
//

#ifndef Cube_hpp
#define Cube_hpp

#include "Mesh.hpp"
#include "Time.hpp"
#include "CookieFactory.hpp"
#include "SceneObject.hpp"
#include "MeshStruct.h"

namespace cookie {
	class Cube : public SceneObject {
	public:
		Cube(float x, float y, float z);

		~Cube() override = default;

		static const int meshSize = 8;

		static std::unique_ptr<MeshData> genMesh() {
			std::vector<Vertex> vertices;
			std::vector<Texture> textures;
			std::vector<unsigned int> indices;
			return std::make_unique<MeshData>(vertices, indices, textures);
		}
	};
}

#endif /* Cube_hpp */
