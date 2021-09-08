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
		Vertex(const Vertex &) = delete;
		Vertex &operator=(const Vertex &) = delete;
		Vertex(Vertex &&) noexcept ;
	};

	struct Texture {
		enum class Type : char {
			SPECULAR = 's',
			DIFFUSE = 'd'
		};
		unsigned int id;
		std::string path;
		Type type;

		Texture(unsigned int id, std::string path, Type type);
		Texture(unsigned int id, std::string path);
		Texture(const Texture &) = delete;
		Texture &operator=(const Texture &) = delete;
		Texture(Texture &&) noexcept ;
	};

	struct MeshData {
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		MeshData() = default;
		MeshData(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
		MeshData(const MeshData &) = delete;
		MeshData &operator=(const MeshData &) = delete;
		MeshData(MeshData &&) noexcept;
	};
}


#endif //COOKIE_ENGINE_MESHSTRUCT_H
