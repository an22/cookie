//
// Created by Michael on 6/4/2022.
//

#include "Transformation.hpp"
#include <glm/gtx/transform.hpp>

namespace cookie {
	Transformation::Transformation(
			const glm::vec3 &position,
			const glm::quat &rotation,
			const glm::vec3 &scale
	) : translation(position), rotation(rotation), scaling(scale), modelMat(glm::mat4(1.0f)), parentModelMat(glm::mat4(1.0f)), transformationMat(glm::mat4(1.0f)), _isChanged(true) {
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

	const glm::mat4 &Transformation::getModelMatrix() {
		return modelMat;
	}

	const glm::mat4 &Transformation::getGlobalTransformationMatrix() {
		return transformationMat;
	}

	void Transformation::regenerateModelMatrix() {
		auto scale = glm::scale(scaling);
		auto rotate = glm::mat4_cast(rotation);
		auto translate = glm::translate(translation);
		modelMat = translate * rotate * scale;
		invalidateTransformation();
	}

	void Transformation::setModelMatrix(const glm::mat4 &matModel) {
		modelMat = matModel;
	}

	void Transformation::setParent(const std::shared_ptr<Transformation> &transformation) {
		parent = transformation;
	}

	void Transformation::addChild(const std::shared_ptr<Transformation> &child) {
		children.emplace_back(child);
		invalidateChildTransformation();
	}

	void Transformation::removeChild(const std::shared_ptr<Transformation> &child) {
		child->parent.reset();
		children.erase(std::remove(children.begin(), children.end(), child), children.end());
	}

	void Transformation::invalidateTransformation() {
		if (!parent.expired()) {
			transformationMat = parent.lock()->transformationMat * modelMat;
		} else {
			transformationMat = modelMat;
		}
		invalidateChildTransformation();
	}

	bool Transformation::isChanged() const {
		return _isChanged;
	}

	void Transformation::setIsChanged(bool isChanged) {
		_isChanged = isChanged;
	}

	void Transformation::invalidateChildTransformation() {
		for (auto &child: children) {
			child->invalidateTransformation();
		}
	}
}