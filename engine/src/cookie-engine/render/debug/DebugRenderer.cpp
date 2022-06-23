//
// Created by Michael on 6/15/2022.
//

#include "DebugRenderer.h"
#include "SceneObject.hpp"
#include "MeshComponent.hpp"
#include "CookieFactory.hpp"
#include <iterator>

namespace cookie {
	DebugRenderer::DebugRenderer() : boundsRenderer(CookieFactory::provideBoundsRenderer()) {
	}

	DebugRenderer::~DebugRenderer() = default;

	void DebugRenderer::saveToGPU() {
		boundsRenderer->saveToGPU(sceneObjects);
	}

	void DebugRenderer::addObject(std::shared_ptr<SceneObject> sceneObject) {
		auto it = sceneObject->childrenBegin();
		auto end = sceneObject->childrenEnd();
		while (it != end) {
			addObject(*it);
			it++;
		}
		sceneObjects.emplace_back(std::move(sceneObject));
	}

	void DebugRenderer::removeObject(const std::shared_ptr<SceneObject> &sceneObject) {
		const auto &it = std::find(sceneObjects.begin(), sceneObjects.end(), sceneObject);
		sceneObjects.erase(it);
	}

	void DebugRenderer::render(const DrawUtils &drawUtils) {
		boundsRenderer->render(drawUtils);
	}
}
