//
// Created by Antiufieiev Michael on 12.08.2021.
//

#include "MeshStruct.h"

#include <utility>

namespace cookie {

	MeshData::MeshData(
			std::vector<Vertex> vertices,
			std::vector<unsigned int> indices,
			std::vector<Texture> textures,
			glm::mat4 transformation
	) : vertices(std::move(vertices)),
		indices(std::move(indices)),
		textures(std::move(textures)),
		transformation(transformation){
	}

	MeshData::MeshData(MeshData &&meshData) noexcept: vertices(std::move(meshData.vertices)),
													  indices(std::move(meshData.indices)),
													  textures(std::move(meshData.textures)),
													  transformation(meshData.transformation){
	}

	Vertex::Vertex(
			const glm::vec3 &position,
			const glm::vec3 &normal,
			const glm::vec2 &texCoords
	) : position(position),
		normal(normal),
		texCoords(texCoords) {
	}

	Vertex::Vertex(Vertex &&vertex) noexcept: position(vertex.position),
											  texCoords(vertex.texCoords),
											  normal(vertex.normal) {
	}

	Texture::Texture(unsigned int id, std::string path, Type type) : id(id),
																	 path(std::move(path)),
																	 type(type) {
	}

	Texture::Texture(unsigned int id, std::string path) : id(id),
														  path(std::move(path)),
														  type(Type::DIFFUSE) {
	}

	Texture::Texture(Texture &&texture) noexcept : id(texture.id),
										  path(std::move(texture.path)),
										  type(texture.type) {
		texture.id = 0;
	}
}
