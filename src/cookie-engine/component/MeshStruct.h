//
// Created by Antiufieiev Michael on 12.08.2021.
//

#ifndef COOKIE_ENGINE_MESHSTRUCT_H
#define COOKIE_ENGINE_MESHSTRUCT_H

#include <glm/glm.hpp>
#include "Material.h"

namespace cookie {
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;
		int32_t matrixOffset;

		Vertex(const glm::vec3 &position, const glm::vec3 &normal, const glm::vec2 &texCoords);
		Vertex() = default;
		Vertex(const Vertex &);
		Vertex &operator=(const Vertex &);
		Vertex(Vertex &&) noexcept;
	};

	struct MeshData {
		std::string name;
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::shared_ptr<Material> material;


		MeshData() = default;
		MeshData(
				std::string name,
				std::vector<Vertex> &vertices,
				std::vector<unsigned int> &indices,
				std::shared_ptr<Material> &material
		);
		MeshData(const MeshData &) = delete;
		MeshData &operator=(const MeshData &) = delete;
		MeshData(MeshData &&) noexcept;
	};
}


#endif //COOKIE_ENGINE_MESHSTRUCT_H
