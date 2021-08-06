//
//  SceneObject.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include "SceneObject.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <typeinfo>
#include <type_traits>

namespace cookie {
SceneObject::SceneObject() {
	
}

SceneObject::SceneObject(glm::vec3 pos) {
	setPosition(pos);
}

SceneObject::SceneObject(float x, float y, float z) {
	setPosition(x, y, z);
}

SceneObject::~SceneObject() {
	
}

template <class ComponentType>
void SceneObject::addComponent(std::unique_ptr<ComponentType> component) {
	static_assert(std::is_base_of<Component, ComponentType>::value, "type parameter of this class must derive from Component class");
	
	components[typeid(ComponentType)] = component;
}

template <class ComponentType>
ComponentType& SceneObject::removeComponent(std::type_index key) {
	return static_cast<ComponentType>(components.extract(key));
}

template <class ComponentType>
ComponentType& SceneObject::getComponent() {
	return static_cast<ComponentType>(components[typeid(ComponentType)]);
}

const glm::mat4& SceneObject::getModelMat() {
	return modelMat;
}

bool SceneObject::isStatic() {
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

void SceneObject::setPosition(const glm::vec3 &position) {
	this->position = position;
	modelMat = glm::translate(glm::mat4(1.0f), position);
}

void SceneObject::setPosition(float x, float y, float z) {
	this->position = glm::vec3(x, y, z);
	modelMat = glm::translate(glm::mat4(1.0f), position);
}
}
