//
// Created by Antiufieiev Michael on 10.10.2021.
//

#include <Mesh.hpp>
#include <GLErrorHandler.hpp>
#include "BatchManager.hpp"
#include "CookieFactory.hpp"

void cookie::BatchManager::onNewObject(const std::shared_ptr<SceneObject> &sceneObject) {
	auto meshComponent = sceneObject->getComponent<Mesh>();
	if (meshComponent != nullptr && !meshComponent->getVertices().empty()) {
		auto& batch = batchMap[meshComponent->getMaterial()];
		if(batch == nullptr) {
			std::unique_ptr<Batch> newBatch = std::make_unique<Batch>(meshComponent->getMaterial());
			newBatch->addObject(sceneObject);
			batchMap[meshComponent->getMaterial()] = std::move(newBatch);
		}else {
			batch->addObject(sceneObject);
		}
	}
	auto it = sceneObject->childrenBegin();
	auto end = sceneObject->childrenEnd();
	while (it != end) {
		onNewObject(*it);
		it++;
	}
}


//TODO multithreading
void cookie::BatchManager::syncWithVideoBuffer() {
	for (auto &entry: batchMap) {
		entry.second->syncWithVideoBuffer();
	}
}

cookie::BatchManager::BatchManager() : batchMap{} {
}

void cookie::BatchManager::draw(const cookie::DrawUtils &drawUtils) const {
	for (auto &entry: batchMap) {;
		entry.second->draw(drawUtils);
	}
}
