//
//  SceneObject.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include <algorithm>
#include "SceneObject.hpp"
#include "Sector.hpp"
#include "MeshComponent.hpp"
#include "MeshStruct.h"
#include "Material.h"
#include "TextureProcessor.hpp"
#include "DrawUtils.h"
#include "Transformation.hpp"
#include "Shader.hpp"
#include "AssetImporter.hpp"
#include "SectorComponent.hpp"

namespace cookie {

	std::atomic_uint32_t SceneObject::current_id = 0;

	SceneObject::SceneObject() : transformation(
			std::make_shared<Transformation>(
					Transformation(
							glm::vec3(0.0f),
							glm::identity<glm::quat>(),
							glm::vec3(1.0f)
					))), children(), id(current_id++), is_static(true) {
	}

	std::shared_ptr<SceneObject> SceneObject::fromPath(const std::string &path) {
		auto obj = std::make_shared<SceneObject>();
		AssetImporter::importMesh(obj, path);
		return obj;
	}

	SceneObject::~SceneObject() = default;

	const glm::mat4 &SceneObject::getModelMat() const {
		return transformation->getGlobalTransformationMatrix();
	}

	bool SceneObject::isStatic() const {
		return is_static;
	}

	void SceneObject::setStatic(bool isStatic) {
		this->is_static = isStatic;
	}

	void SceneObject::addChild(const std::shared_ptr<SceneObject> &child) {
		child->transformation->setParent(transformation);
		child->addComponent(std::make_shared<SectorComponent>(child));
		transformation->addChild(child->transformation);
		children.push_back(std::shared_ptr(child));
	}

	std::shared_ptr<SceneObject> SceneObject::getChildAt(unsigned int position) {
		return children[position];
	}

	void SceneObject::removeChild(const std::shared_ptr<SceneObject> &child) {
		transformation->removeChild(child->transformation);
		children.erase(std::remove(children.begin(), children.end(), child), children.end());
	}

	SceneObject::PtrSceneObjVector::iterator SceneObject::childrenBegin() noexcept {
		return children.begin();
	}

	SceneObject::PtrSceneObjVector::iterator SceneObject::childrenEnd() noexcept {
		return children.end();
	}

	uint32_t SceneObject::getId() const {
		return id;
	}

	const std::shared_ptr<Transformation> &SceneObject::getTransformation() const {
		return transformation;
	}

	const std::string &SceneObject::getName() const {
		return name;
	}

	void SceneObject::setName(const std::string &newName) {
		name = newName;
	}

	void SceneObject::onCreate() {}

	void SceneObject::onUpdate() {}

	void SceneObject::onPostUpdate() {}
}
