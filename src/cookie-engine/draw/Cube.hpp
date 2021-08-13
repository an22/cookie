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
			vertices.emplace_back(glm::vec3(-1.0, -1.0, 1.0), glm::vec3(), glm::vec2());
			vertices.emplace_back(glm::vec3(1.0, -1.0, 1.0), glm::vec3(), glm::vec2());
			vertices.emplace_back(glm::vec3(1.0, 1.0, 1.0), glm::vec3(), glm::vec2());
			vertices.emplace_back(glm::vec3(-1.0, 1.0, 1.0), glm::vec3(), glm::vec2());
			vertices.emplace_back(glm::vec3(-1.0, -1.0, -1.0), glm::vec3(), glm::vec2());
			vertices.emplace_back(glm::vec3(1.0, -1.0, -1.0), glm::vec3(), glm::vec2());
			vertices.emplace_back(glm::vec3(1.0, 1.0, -1.0), glm::vec3(), glm::vec2());
			vertices.emplace_back(glm::vec3(-1.0, 1.0, -1.0), glm::vec3(), glm::vec2());
			uint32_t _indices[36] = {
					// front
					0, 1, 2,
					2, 3, 0,
					// right
					1, 5, 6,
					6, 2, 1,
					// back
					7, 6, 5,
					5, 4, 7,
					// left
					4, 0, 3,
					3, 7, 4,
					// bottom
					4, 5, 1,
					1, 0, 4,
					// top
					3, 2, 6,
					6, 7, 3
			};
			std::vector<uint32_t> indices(_indices, _indices + 36);
			return std::make_unique<MeshData>(vertices, indices, textures);
		}
	};
}

#endif /* Cube_hpp */
