//
// Created by Michael on 6/16/2022.
//

#include "SubRenderable.hpp"
#include <stdexcept>

namespace cookie {

	void SubRenderable::saveToGPU() {
		throw std::runtime_error(
				"This renderer intends to be a part of some other renderer "
				"and do not support direct object storage. "
				"Use saveToGPU(const std::list<std::shared_ptr<SceneObject>> &sceneObjects) instead"
		);
	}

	SubRenderable::SubRenderable(const std::shared_ptr<Material> &material) : Renderable(material) {}
}
