//
// Created by Michael on 6/16/2022.
//

#ifndef COOKIE_ENGINE_SUBRENDERABLE_HPP
#define COOKIE_ENGINE_SUBRENDERABLE_HPP

#include "Renderable.hpp"

namespace cookie {
	class SceneObject;

	class SubRenderable : public Renderable {
	public:
		explicit SubRenderable(const std::shared_ptr<Material> &material);
		void saveToGPU() final;
		virtual void saveToGPU(const std::list<std::shared_ptr<SceneObject>>& sceneObjects) = 0;
	};
}

#endif //COOKIE_ENGINE_SUBRENDERABLE_HPP
