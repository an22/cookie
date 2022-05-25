//
//  SceneObject.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include "SceneObject.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include "asset/AssetImporter.hpp"
#include <Mesh.hpp>

namespace cookie {

	SceneObject::SceneObject() : transformation(
			Transformation(
					glm::vec3(0.0f, 0.0f, 0.0f),
					glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
					glm::vec3(1.0f, 1.0f, 1.0f)
			)), children() {
	}

	SceneObject::SceneObject(glm::mat4 transformation) : transformation(
			Transformation(
					glm::vec3(0, 0, 0),
					glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
					glm::vec3(1.0f, 1.0f, 1.0f)
			)
	), children() {
	}

	SceneObject::SceneObject(glm::vec3 pos) : transformation(
			Transformation(
					glm::vec3(0, 0, 0),
					glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
					glm::vec3(1.0f, 1.0f, 1.0f)
			)), children() {
	}

	SceneObject::SceneObject(const std::string &path, float x, float y, float z) : SceneObject(
			path,
			glm::vec3(x, y, z)) {
	}

	SceneObject::SceneObject(const std::string &path, glm::vec3 pos) : SceneObject(pos) {
		AssetImporter::importMesh(*this, path);
	}

	SceneObject::~SceneObject() = default;

	const glm::mat4 &SceneObject::getModelMat() const {
		return transformation.modelMat;
	}

	bool SceneObject::isStatic() const {
		return is_static;
	}

	void SceneObject::setStatic(bool isStatic) {
		this->is_static = isStatic;
	}

	void SceneObject::draw(const cookie::DrawUtils &utils) {
		for (auto &child: children) {
			child->draw(utils);
		}
		auto mesh = getComponent<Mesh>();
		auto shader = getComponent<Shader>();
		if (!mesh) return;
		if (!shader) return;
		shader->use();
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

	Transformation::Transformation(
			const glm::vec3 &position,
			const glm::quat &rotation,
			const glm::vec3 &scale
	) : translation(position), rotation(rotation), scaling(scale), modelMat(glm::mat4(1)) {
		regenerateModelMatrix();
	}

	void Transformation::translate(const glm::vec3 &vTranslate) {
		translation += vTranslate;
		regenerateModelMatrix();
	}

	void Transformation::scale(const glm::vec3 &vScale) {
		scaling *= vScale;
		regenerateModelMatrix();
	}

	void Transformation::rotate(const glm::quat &qRotate) {
		rotation *= qRotate;
		regenerateModelMatrix();
	}

	void Transformation::transform(
			const glm::vec3 &vTranslate,
			const glm::quat &qRotate,
			const glm::vec3 &vScale
	) {
		translation += vTranslate;
		scaling *= vScale;
		rotation *= qRotate;
		regenerateModelMatrix();
	}

	void Transformation::regenerateModelMatrix() {
		modelMat = glm::mat4(1);
		modelMat = glm::translate(modelMat, translation);
		modelMat = glm::scale(modelMat, scaling);
		modelMat = glm::toMat4(rotation) * modelMat;
	}

	void Transformation::setModelMatrix(const glm::mat4 &matModel) {
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(matModel, scaling, rotation, translation, skew, perspective);
		rotation = glm::conjugate(rotation);
		modelMat = matModel;
	}
}
