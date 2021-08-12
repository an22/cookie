//
// Created by Antiufieiev Michael on 12.08.2021.
//

#include "MeshStruct.h"

namespace cookie {
    Vertex::Vertex(
            const glm::vec3 &position,
            const glm::vec3 &normal,
            const glm::vec2 &texCoords
    ) : position(position), normal(normal), texCoords(texCoords) {}

    Texture::Texture(uint32_t id, std::string type) : id(id), type(std::move(type)) {}

    MeshData::MeshData(
            std::vector<Vertex> vertices,
            std::vector<uint32_t> indices,
            std::vector<Texture> textures
    ) : vertices(std::move(vertices)), indices(std::move(indices)), textures(std::move(textures)) {}
}
