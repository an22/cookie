//
//  SceneObject.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include "SceneObject.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <type_traits>
#include <Mesh.hpp>

namespace cookie {
    SceneObject::SceneObject() {
        position = glm::vec3(0, 0, 0);
        modelMat = glm::mat4();
    }

    SceneObject::SceneObject(glm::vec3 pos) : position(pos) {
        modelMat = glm::translate(glm::mat4(1), pos);
    }

    SceneObject::SceneObject(float x, float y, float z) : SceneObject(glm::vec3(x, y, z)) {
    }

    SceneObject::~SceneObject() = default;

    const glm::mat4 &SceneObject::getModelMat() {
        return modelMat;
    }

    bool SceneObject::isStatic() const {
        return is_static;
    }

    void SceneObject::transform(const glm::mat4 &transformation) {
        if (is_static) {
            return;
        }
        modelMat = transformation * modelMat;
    }

    void SceneObject::setStatic(bool isStatic) {
        this->is_static = isStatic;
    }

    void SceneObject::setPosition(const glm::vec3 &newPosition) {
        position = newPosition;
        modelMat = glm::translate(glm::mat4(1.0f), position);
    }

    void SceneObject::setPosition(float x, float y, float z) {
        this->position = glm::vec3(x, y, z);
        modelMat = glm::translate(glm::mat4(1.0f), position);
    }
    void SceneObject::draw(cookie::DrawUtils &utils, glm::mat4 &viewMatrix, glm::mat4 &projMatrix) {
        auto mesh = getComponent<Mesh>();
        auto shader = getComponent<Shader>();
        if (!mesh) return;
        if (!shader) return;
        auto mvMatrix = viewMatrix * modelMat;
        shader->setMatrix4("mv_matrix", mvMatrix);
        shader->setMatrix4("proj_matrix", projMatrix);
        mesh->onPreDraw(*shader);
        if (!mesh->getIndices().empty()) {
            utils.drawElements(mesh->getIndices().size());
        } else {
            utils.drawArrays(0, mesh->getVertices().size());
        }
    }
}
