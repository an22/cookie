//
// Created by Michael on 6/11/2022.
//
#include "Component.hpp"
#include "SceneObject.hpp"

namespace cookie {

	Component::Component(const std::shared_ptr<SceneObject> &objPtr) : owner(objPtr) {
	}
}