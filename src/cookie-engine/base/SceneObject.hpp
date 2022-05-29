//
//  SceneObject_hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 06.07.2021.
//

#ifndef SceneObject_hpp
#define SceneObject_hpp

#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <typeindex>
#include <DrawUtils.h>
#include <Time.hpp>
#include <type_quat.hpp>
#include "Component.hpp"

namespace cookie {

	struct Transformation {
		glm::vec3 translation;
		glm::quat rotation;
		glm::vec3 scaling;
		glm::mat4 modelMat;

		glm::mat4 parentModelMat;
		glm::mat4 transformationMat;

		std::weak_ptr<Transformation> parent;

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
		void setParent(const std::shared_ptr<Transformation> &transformation);
		void setModelMatrix(const glm::mat4 &matModel);
		void regenerateModelMatrix();
	};

	class SceneObject {
		typedef std::vector<std::shared_ptr<SceneObject>> PtrSceneObjVector;
		typedef std::unordered_map<std::type_index, std::shared_ptr<Component>> ComponentMap;
	protected:
		bool is_static = false;
		ComponentMap components;
		PtrSceneObjVector children;
	public:
		std::shared_ptr<Transformation> transformation;
		std::string name;
		explicit SceneObject(glm::vec3 pos);
		explicit SceneObject(glm::mat4 mTransformation);
		SceneObject(const std::string &path, glm::vec3 pos);
		SceneObject();
		SceneObject(const std::string &path, float x, float y, float z);
		virtual ~SceneObject();
		[[nodiscard]] const glm::mat4 &getModelMat() const;
		[[nodiscard]] bool isStatic() const;
		virtual void setStatic(bool isStatic);
		virtual void draw(const DrawUtils &utils);
		virtual void addChild(const std::shared_ptr<SceneObject> &child);
		virtual std::shared_ptr<SceneObject> getChildAt(unsigned int position);
		virtual void removeChild(const std::shared_ptr<SceneObject> &child);
		PtrSceneObjVector::iterator childrenBegin() noexcept;
		PtrSceneObjVector::iterator childrenEnd() noexcept;
		void invalidate();

		//Templates
		template<class ComponentType>
		void addComponent(std::shared_ptr<ComponentType> component) {
			static_assert(
					std::is_base_of<Component, ComponentType>::value,
					"type parameter of this class must derive from Component class"
			);
			components[typeid(ComponentType)] = std::shared_ptr(component);
		}

		template<class ComponentType>
		ComponentType &removeComponent() {
			auto component = std::move(components[typeid(ComponentType)]);
			components.erase(typeid(ComponentType));
			return dynamic_cast<ComponentType>(component);
		}

		template<class ComponentType>
		std::shared_ptr<ComponentType> getComponent() {
			auto item = components.find(typeid(ComponentType));
			if (item != components.end()) {
				return std::dynamic_pointer_cast<ComponentType>(item->second);
			}
			return nullptr;
		}
	};
}

#endif /* SceneObject_hpp */
