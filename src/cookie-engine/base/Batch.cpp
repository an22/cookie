//
// Created by Antiufieiev Michael on 10.10.2021.
//

#include "Batch.hpp"

void cookie::Batch::addObject(std::shared_ptr<SceneObject> sceneObject) {
	sceneObjects.push_back(std::move(sceneObject));
}

void cookie::Batch::removeObject(std::shared_ptr<SceneObject> sceneObject) {
	const auto &it = std::find(sceneObjects.begin(), sceneObjects.end(), sceneObject);
	sceneObjects.erase(it);
}

void cookie::Batch::syncWithVideoBuffer(const cookie::BufferStorage &bufferStorage) {
	for (auto &sceneObject: sceneObjects) {
		bufferStorage.saveToBuffer();
	}
}
