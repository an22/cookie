//
// Created by Antiufieiev Michael on 12.08.2021.
//

#ifndef COOKIE_ENGINE_MESHSTRUCT_H
#define COOKIE_ENGINE_MESHSTRUCT_H

#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace cookie {
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;

		Vertex(const glm::vec3 &position, const glm::vec3 &normal, const glm::vec2 &texCoords);
	};

	struct Texture {
		uint32_t id;
		std::string type;

		Texture(uint32_t id, std::string type);
	};

	struct MeshData {
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		std::vector<Texture> textures;

		MeshData() = default;
		MeshData(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Texture> textures);
	};
}


#endif //COOKIE_ENGINE_MESHSTRUCT_H
