//
// Created by Michael on 6/15/2022.
//

#ifndef COOKIE_ENGINE_DEBUGRENDERER_H
#define COOKIE_ENGINE_DEBUGRENDERER_H

#include <list>
#include <memory>
#include <glm/mat4x4.hpp>
#include "Renderable.hpp"
#include "BoundsRenderer.h"

namespace cookie {
	class SceneObject;
	class Material;
	class BoundsRenderer;

	class DebugRenderer {
	private:
		std::list<std::shared_ptr<SceneObject>> sceneObjects;
		std::shared_ptr<BoundsRenderer> boundsRenderer;
	public:
		DebugRenderer();
		~DebugRenderer();
		void addObject(std::shared_ptr<SceneObject> sceneObject);
		void removeObject(const std::shared_ptr<SceneObject> &sceneObject);
		void saveToGPU();
		void render(const cookie::DrawUtils &drawUtils);
	};
}

#endif //COOKIE_ENGINE_DEBUGRENDERER_H
