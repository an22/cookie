//
//  SceneObject.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include "SceneObject.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "AssetImporter.hpp"
#include <Mesh.hpp>

namespace cookie {
	int SceneObject::objCount = 0;

	SceneObject::SceneObject() : position(glm::vec3(0, 0, 0)),
								 modelMat(glm::mat4(1)),
								 children() {
	}

	SceneObject::SceneObject(glm::vec3 pos) : position(pos),
											  modelMat(glm::translate(glm::mat4(1), pos)),
											  children() {
	}

	SceneObject::SceneObject(const std::string &path, float x, float y, float z) : SceneObject(path,
																							   glm::vec3(x, y, z)) {
	}

	SceneObject::SceneObject(const std::string &path, glm::vec3 pos) : SceneObject(pos) {
		auto meshes = std::move(AssetImporter::importMesh(path));
		if (meshes.size() > 1) {
			auto iterator = meshes.begin();
			while (iterator != meshes.end()) {
				auto sceneObject = std::make_shared<SceneObject>();
				sceneObject->addComponent(std::make_unique<Mesh>(std::move(*iterator)));
				sceneObject->addComponent(CookieFactory::provideShader(
						"/Users/antiufieievmichael/Guides/cookie-engine/src/cookie-engine/shader/vertex/vertex.glsl",
						"/Users/antiufieievmichael/Guides/cookie-engine/src/cookie-engine/shader/fragment/fragment.glsl"
				));
				addChild(sceneObject);
				iterator++;
			}
		} else {
			addComponent(std::make_unique<Mesh>(std::move(meshes[0])));
		}
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

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

	void SceneObject::draw(cookie::DrawUtils &utils, glm::mat4 &viewMatrix, glm::mat4 &projMatrix) {
		auto iterator = children.begin();
		while (iterator != children.end()) {
			iterator->get()->draw(utils, viewMatrix, projMatrix);
			iterator++;
		}
		auto mesh = getComponent<Mesh>();
		auto shader = getComponent<Shader>();
		if (!mesh) return;
		if (!shader) return;
		glm::mat4 a = viewMatrix * modelMat;
		shader->setMatrix4("mv_matrix", a);
		shader->setMatrix4("proj_matrix", projMatrix);
		mesh->onPreDraw(*shader);
		if (!mesh->getIndices().empty()) {
			utils.drawElements(mesh->getIndices().size());
		} else {
			utils.drawArrays(0, mesh->getVertices().size());
		}
	}

#pragma clang diagnostic pop

	void SceneObject::addChild(const std::shared_ptr<SceneObject> &child) {
		children.push_back(child);
	}

	void SceneObject::removeChild(const std::shared_ptr<SceneObject> &child) {
		children.erase(std::remove(children.begin(), children.end(), child), children.end());
	}
}
