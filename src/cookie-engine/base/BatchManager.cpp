//
// Created by Antiufieiev Michael on 10.10.2021.
//

#include "BatchManager.hpp"
#include "CookieFactory.hpp"

void cookie::BatchManager::onNewObject(const std::shared_ptr<SceneObject>& sceneObject) {
	auto meshComponent = sceneObject->getComponent<MeshData>();
	if (meshComponent != nullptr && !meshComponent->vertices.empty()) {
		auto& batch = batchMap[meshComponent->material];
		batch->addObject(sceneObject);
		auto it = sceneObject->childrenBegin();
		auto end = sceneObject->childrenEnd();
		while(it != end) {
			onNewObject(*it);
			it++;
		}
	}
}


//TODO multithreading
void cookie::BatchManager::syncWithVideoBuffer() {
	for (auto& entry : batchMap) {
		entry.second->syncWithVideoBuffer(*bufferStorage);
	}
}

cookie::BatchManager::BatchManager() : bufferStorage(CookieFactory::provideBufferStorage()),
									   batchMap{} {
}
