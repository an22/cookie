//
// Created by Michael on 6/4/2022.
//

#ifndef COOKIE_ENGINE_TRANSFORMATION_HPP
#define COOKIE_ENGINE_TRANSFORMATION_HPP

#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <glm/gtx/quaternion.hpp>

namespace cookie {
	class Transformation {

		glm::vec3 translation;
		glm::quat rotation;
		glm::vec3 scaling;
		glm::mat4 modelMat;

		glm::mat4 parentModelMat;
		glm::mat4 transformationMat;

		bool _isChanged;

		std::vector<std::shared_ptr<Transformation>> children;
		std::weak_ptr<Transformation> parent;

		void invalidateChildTransformation();
	public:
		Transformation(
				const glm::vec3 &position,
				const glm::quat &rotation,
				const glm::vec3 &scale
		);
		void rotate(const glm::quat &qRotate);
		void translate(const glm::vec3 &vTranslate);
		void scale(const glm::vec3 &vScale);
		void transform(
				const glm::vec3 &vTranslate,
				const glm::quat &qRotate,
				const glm::vec3 &vScale
		);
		[[nodiscard]] bool isChanged() const;
		void setIsChanged(bool isChanged);
		const glm::mat4 &getModelMatrix();
		const glm::mat4 &getGlobalTransformationMatrix();
		void setParent(const std::shared_ptr<Transformation> &transformation);
		void setModelMatrix(const glm::mat4 &matModel);
		void addChild(const std::shared_ptr<Transformation> &child);
		void removeChild(const std::shared_ptr<Transformation> &child);
		void regenerateModelMatrix();
		void invalidateTransformation();
	};
}

#endif //COOKIE_ENGINE_TRANSFORMATION_HPP
