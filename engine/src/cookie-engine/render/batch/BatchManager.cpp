//
// Created by Antiufieiev Michael on 10.10.2021.
//

#include <MeshComponent.hpp>
#include "BatchManager.hpp"
#include "SceneObject.hpp"
#include "BufferStorage.hpp"

namespace cookie {

	void BatchManager::onNewObject(const std::shared_ptr<SceneObject> &sceneObject) {
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

	void BatchManager::onStart() {
		for (const auto &entry: batchMap) {
			entry.second->saveToGPU();
		}
	}

	BatchManager::BatchManager() : batchMap{} {
	}

	void BatchManager::render(const DrawUtils &drawUtils) const {
		for (const auto &entry: batchMap) {
			entry.second->render(drawUtils);
		}
	}
}
