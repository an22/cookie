//
//  Mesh.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 06.08.2021.
//

#include "Mesh.hpp"
#include "CookieFactory.hpp"
#include "DrawUtils.h"
#include <utility>

namespace cookie {

    Mesh::Mesh(
            const std::vector<Vertex> &vertices,
            const std::vector<uint32_t> &indices,
            const std::vector<Texture> &textures
    ) {
        std::unique_ptr<PlatformSpecificBufferData> data = CookieFactory::provideBufferData(BufferType::VERTEX_BUFFER);
        bufferStorage = CookieFactory::provideBufferStorage(1);
        bufferStorage->saveToBuffer(vertices.size(), vertices.data(), std::move(data));
    }

    Mesh::Mesh(const std::string &path) {
        //TODO asset importer
    }
    const std::vector<Vertex> &Mesh::getVertices() const {
        return vertices;
    }
    const std::vector<uint32_t> &Mesh::getIndices() const {
        return indices;
    }
    const std::vector<Texture> &Mesh::getTextures() const {
        return textures;
    }

    void Mesh::onPreDraw(Shader &shader) {
        shader.use();
        bufferStorage->bind();
    }

    void Mesh::onPreDraw(Material &shader) {
        shader.onPreDraw();
        bufferStorage->bind();
    }

    Vertex::Vertex(
            const glm::vec3 &position,
            const glm::vec3 &normal,
            const glm::vec2 &texCoords
    ) : position(position), normal(normal), texCoords(texCoords) {
    }

    Texture::Texture(uint32_t id, std::string type) : id(id), type(std::move(type)) {}
}
