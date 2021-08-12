//
// Created by Antiufieiev Michael on 08.08.2021.
//

#include "Cube.hpp"
#include <vector>
namespace cookie {

    Cube::Cube(float x, float y, float z) : SceneObject(x, y, z) {
        auto vertices = genMesh();
        auto vector = std::vector<Vertex>(vertices, vertices + 36);
        addComponent<Mesh>(std::make_unique<Mesh>(vector, std::vector<uint32_t>(), std::vector<Texture>()));
        auto shader = CookieFactory::provideShader(
                "/Users/antiufieievmichael/Guides/cookie-engine/src/cookie-engine/shader/vertex/24cubes.glsl",
                "/Users/antiufieievmichael/Guides/cookie-engine/src/cookie-engine/shader/fragment/fragment.glsl"
                );
        addComponent<Shader>(std::move(shader));
        delete[] vertices;
    }

    void Cube::draw(cookie::DrawUtils &utils, glm::mat4 &viewMatrix, glm::mat4 &projMatrix) {
        auto &shader = getComponent<Shader>();
        shader.setMatrix4("v_matrix", viewMatrix);
        shader.setMatrix4("proj_matrix", projMatrix);
        shader.setFloat("timeFactor", (float) time->getProgramTime());
        auto &mesh = getComponent<Mesh>();
        mesh.onPreDraw(shader);
        utils.enableVertexAttribute(0);
    }

}
