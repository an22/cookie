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
		AssetImporter::importMesh(*this, path);
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

	void SceneObject::draw(const cookie::DrawUtils &utils, const glm::mat4 &viewMatrix, const glm::mat4 &projMatrix) {
		for (auto& child : children) {
			child->draw(utils, viewMatrix, projMatrix);
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

	void SceneObject::addChild(const std::shared_ptr<SceneObject> &child) {
		children.push_back(std::shared_ptr(child));
	}

	std::shared_ptr<SceneObject> SceneObject::getChildAt(unsigned int position) {
		return children[position];
	}

	void SceneObject::removeChild(const std::shared_ptr<SceneObject> &child) {
		children.erase(std::remove(children.begin(), children.end(), child), children.end());
	}

	SceneObject::PtrSceneObjVector::iterator SceneObject::childrenBegin() noexcept {
		return children.begin();
	}

	SceneObject::PtrSceneObjVector::iterator SceneObject::childrenEnd() noexcept {
		return children.end();
	}
}
