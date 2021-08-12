//
//  Cube.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 06.07.2021.
//

#ifndef Cube_hpp
#define Cube_hpp

#include "Mesh.hpp"
#include "Time.hpp"
#include "CookieFactory.hpp"
#include "SceneObject.hpp"

namespace cookie {
    class Cube : public SceneObject {
    private:
        std::unique_ptr<Time> time = CookieFactory::provideTimeManager();
    public:
        Cube(float x, float y, float z);

        ~Cube() override = default;

        void draw(DrawUtils &utils, glm::mat4 &viewMatrix, glm::mat4 &projMatrix) override;

        static const int meshSize = 36;

        static Vertex *genMesh() {
            auto *mesh = new Vertex[meshSize]{
                    Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(), glm::vec2()),
                    Vertex(glm::vec3(-1.0f, 1.0f, -1.0), glm::vec3(), glm::vec2())
            };
            return mesh;
        }
    };
}

#endif /* Cube_hpp */
