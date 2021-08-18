//
// Created by Antiufieiev Michael on 12.08.2021.
//

#ifndef COOKIE_ENGINE_MESHSTRUCT_H
#define COOKIE_ENGINE_MESHSTRUCT_H

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <assimp/scene.h>

namespace cookie {
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;

		Vertex(const glm::vec3 &position, const glm::vec3 &normal, const glm::vec2 &texCoords);
		Vertex() = default;
	};

	struct Texture {
		enum class Type: char {
			SPECULAR = 's',
			DIFFUSE = 'd'
		};
		unsigned int id;
		std::string path;
		Type type;

		Texture(unsigned int id, std::string path, Type type);
		Texture(unsigned int id, std::string path);
	};

	struct MeshData {
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		MeshData() = default;
		MeshData(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	};
}


#endif //COOKIE_ENGINE_MESHSTRUCT_H
