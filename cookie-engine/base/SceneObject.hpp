//
//  SceneObject_hpp
//  lighting-test
//
//  Created by Antiufieiev Michael on 06.07.2021.
//

#ifndef SceneObject_hpp
#define SceneObject_hpp

#include <glm/glm.hpp>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include <type_traits>
#include "Component.h"

class SceneObject {
private:
	bool is_static = true;
	
	glm::vec3 position;
	glm::mat4 modelMat;
	
	std::unordered_map<std::type_index, std::unique_ptr<Component>> components;
public:
	
	SceneObject() {
		
	}
	
	SceneObject(glm::vec3 pos) {
		setPosition(pos);
	}
	
	SceneObject(float x, float y, float z) {
		setPosition(x, y, z);
	}
	
	template <class ComponentType>
	void addComponent(std::unique_ptr<ComponentType> component) {
		static_assert(std::is_base_of<Component, ComponentType>::value, "type parameter of this class must derive from Component class");
		components[typeid(ComponentType)] = component;
	}
	
	template <class ComponentType>
	ComponentType& removeComponent(std::type_index key) {
		return static_cast<ComponentType>(components.extract(key));
	}
	
	template <class ComponentType>
	ComponentType& getComponent() {
		return static_cast<ComponentType>(components[typeid(ComponentType)]);
	}
	
	const glm::mat4& getModelMat() {
		return modelMat;
	}
	
	bool isStatic() {
		return is_static;
	}
	
	//region virtual
	
	virtual void transform(const glm::mat4 &transformation) {
		if (is_static) {
			return;
		}
		modelMat = transformation * modelMat;
	}
	
	virtual void setStatic(bool isStatic) {
		this->is_static = isStatic;
	}
	
	virtual void setPosition(const glm::vec3 &position) {
		this->position = position;
		modelMat = glm::translate(glm::mat4(1.0f), position);
	}
	
	virtual void setPosition(float x, float y, float z) {
		this->position = glm::vec3(x, y, z);
		modelMat = glm::translate(glm::mat4(1.0f), position);
	}
	
	virtual ~SceneObject() {}
	
	//endregion virtual
};


#endif /* SceneObject_hpp */
