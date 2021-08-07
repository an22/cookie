//
//  Mesh.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 06.08.2021.
//

#include "Mesh.hpp"

namespace cookie {
    Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<uint32_t> &indices, std::vector<Texture> &textures) {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;
        setupMesh();
    }

    void Mesh::setupMesh() {

    }

    void Mesh::draw(Shader &shader) {
        //TODO draw mesh
    }
}
