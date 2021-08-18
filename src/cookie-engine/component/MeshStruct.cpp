//
// Created by Antiufieiev Michael on 12.08.2021.
//

#include "MeshStruct.h"

#include <utility>

namespace cookie {

	MeshData::MeshData(
			std::vector<Vertex> vertices,
			std::vector<unsigned int> indices,
			std::vector<Texture> textures
	) : vertices(std::move(vertices)),
		indices(std::move(indices)),
		textures(std::move(textures)) {
	}

	Vertex::Vertex(
			const glm::vec3 &position,
			const glm::vec3 &normal,
			const glm::vec2 &texCoords
	) : position(position),
		normal(normal),
		texCoords(texCoords) {
	}

	Texture::Texture(unsigned int id, std::string path, Type type) : id(id),
																	 path(std::move(path)),
																	 type(type) {
	}

	Texture::Texture(unsigned int id, std::string path) : id(id),
														  path(std::move(path)),
														  type(Type::DIFFUSE) {
	}
}
