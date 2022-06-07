//
// Created by Antiufieiev Michael on 12.08.2021.
//

#include "MeshStruct.h"
#include "Material.h"

namespace cookie {

	MeshData::MeshData(
			std::string name,
			std::vector<Vertex> &vertices,
			std::vector<unsigned int> &indices,
			std::shared_ptr<Material> &material
	) : name(std::move(name)),
		vertices(std::move(vertices)),
		indices(std::move(indices)),
		material(std::move(material)) {
	}

	MeshData::MeshData(MeshData &&meshData) noexcept: name(std::move(meshData.name)),
													  vertices(std::move(meshData.vertices)),
													  indices(std::move(meshData.indices)),
													  material(std::move(meshData.material)) {
	}

	MeshData::MeshData() = default;

	MeshData::~MeshData() = default;

	Vertex::Vertex(
			const glm::vec3 &position,
			const glm::vec3 &normal,
			const glm::vec2 &texCoords
	) : position(position),
		normal(normal),
		texCoords(texCoords),
		matrixOffset(-1) {
	}

	Vertex::Vertex(Vertex &&vertex) noexcept: position(vertex.position),
											  texCoords(vertex.texCoords),
											  normal(vertex.normal),
											  matrixOffset(vertex.matrixOffset) {
	}

	Vertex::~Vertex() = default;

	Vertex::Vertex() = default;

	Vertex::Vertex(const Vertex &vertex) = default;

	Vertex &Vertex::operator=(const Vertex &vertex) = default;
}
