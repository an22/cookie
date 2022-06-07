//
// Created by Antiufieiev Michael on 10.10.2021.
//

#include <MeshComponent.hpp>
#include "BatchManager.hpp"
#include "SceneObject.hpp"
#include "BufferStorage.hpp"

void cookie::BatchManager::onNewObject(const std::shared_ptr<SceneObject> &sceneObject) {
	auto meshComponent = sceneObject->getComponent<MeshComponent>();
	if (meshComponent != nullptr && !meshComponent->getVertices().empty()) {
		auto &batch = batchMap[meshComponent->getMaterial()];
		if (batch == nullptr) {
			std::unique_ptr<Batch> newBatch = std::make_unique<Batch>(meshComponent->getMaterial());
			newBatch->addObject(sceneObject);
			batchMap[meshComponent->getMaterial()] = std::move(newBatch);
		} else {
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

void cookie::BatchManager::syncWithVideoBuffer() {
	for (auto &entry: batchMap) {
		entry.second->syncWithVideoBuffer();
	}
}

cookie::BatchManager::BatchManager() : batchMap{} {
}

void cookie::BatchManager::draw(const cookie::DrawUtils &drawUtils) const {
	for (auto &entry: batchMap) {
		entry.second->draw(drawUtils);
	}
}
