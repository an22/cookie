//
// Created by Michael on 6/15/2022.
//

#ifndef COOKIE_ENGINE_BOUNDSRENDERER_H
#define COOKIE_ENGINE_BOUNDSRENDERER_H

#include "SubRenderable.hpp"
#include "MultiDrawConfig.h"

namespace cookie {

	class SceneObject;

	class BoundsRenderer : public SubRenderable {
	private:
		MultiDrawConfig config;
	public:
		explicit BoundsRenderer(const std::shared_ptr<Material> &material);
		void saveToGPU(const std::list<std::shared_ptr<SceneObject>> &sceneObjects) override;
		void render(const cookie::DrawUtils &drawUtils) override;
	};
}

#endif //COOKIE_ENGINE_BOUNDSRENDERER_H
