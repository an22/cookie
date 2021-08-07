//
//  Mesh.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 28.07.2021.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <memory>
#include "Component.hpp"
#include "BufferStorage.hpp"
#include "Shader.hpp"

namespace cookie {

    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
    };

    struct Texture {
        uint32_t id;
        std::string type;
    };

    class Mesh : public Component {
    private:

        std::unique_ptr<BufferStorage> bufferStorage; //TODO provide storage

        void setupMesh();

    public:
        // mesh data
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        std::vector<Texture> textures;

        Mesh(std::vector<Vertex> &vertices, std::vector<uint32_t> &indices, std::vector<Texture> &textures);
        virtual ~Mesh() = default;

        void draw(Shader &shader);
    };

}

#endif /* Mesh_hpp */
