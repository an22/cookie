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
#include "Shader.hpp"
#include "Material.h"

namespace cookie {

    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;

        Vertex(const glm::vec3 &position, const glm::vec3 &normal, const glm::vec2 &texCoords);
    };

    struct Texture {
        uint32_t id;
        std::string type;

        Texture(uint32_t id, std::string type);
    };

    class Mesh : public Component {
    private:
        std::unique_ptr<BufferStorage> bufferStorage;
        // mesh data
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        std::vector<Texture> textures;
    public:
        [[nodiscard]] const std::vector<Vertex> &getVertices() const;
        [[nodiscard]] const std::vector<uint32_t> &getIndices() const;
        [[nodiscard]] const std::vector<Texture> &getTextures() const;

        void onPreDraw(Shader & shader);
        void onPreDraw(Material & shader);
        Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<Texture>& textures);
        explicit Mesh(const std::string& path);
        virtual ~Mesh() = default;
    };

}

#endif /* Mesh_hpp */
