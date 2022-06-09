//
// Created by Michael on 4/25/2022.
//

#include <algorithm>
#include "SceneSectorManager.hpp"
#include "MeshComponent.hpp"
#include "SectorComponent.hpp"
#include "Transformation.hpp"
#include "SceneObject.hpp"
#include "Sector.hpp"

cookie::SceneSectorManager::SceneSectorManager(float sectorSize, const Bounds &bounds)
		: sectorMap(), bounds(bounds), objects() {

}


void cookie::SceneSectorManager::update() {
	std::shared_ptr<MeshComponent> mesh;
	std::shared_ptr<SectorComponent> sectors;
	std::shared_ptr<Sector> currentSector;
	glm::ivec3 cell{};
	for (auto &obj: objects) {
		mesh = obj->getComponent<MeshComponent>();
		sectors = obj->getComponent<SectorComponent>();
		if (obj->getTransformation()->isChanged() && mesh != nullptr) {
			obj->getTransformation()->setIsChanged(false);
			sectors->clear();
			const Bounds& objBounds = mesh->getBounds();
			for (auto x = static_cast<int32_t>(floor(objBounds.min.x)); x <= static_cast<int32_t>(floor(objBounds.max.x)); x++) {
				for (auto y = static_cast<int32_t>(floor(objBounds.min.y)); y <= static_cast<int32_t>(floor(objBounds.max.y)); y++) {
					for (auto z = static_cast<int32_t>(floor(objBounds.min.z)); z <= static_cast<int32_t>(floor(objBounds.max.z)); z++) {
						cell = {x, y, z};
						auto sectorIt = sectorMap.find(cell);
						if (sectorIt != sectorMap.end()) {
							currentSector = sectorIt->second;
						} else {
							auto sector = std::make_shared<Sector>();
							sectorMap.insert(std::make_pair(cell, sector));
							currentSector = sector;
						}
						currentSector->indexList.insert(obj->getId());
						sectors->onNewSector(currentSector);
					}
				}
			}
		}
	}
}

void cookie::SceneSectorManager::addObject(const std::shared_ptr<SceneObject> &sceneObject) {
	objects.emplace_back(sceneObject);
	auto it = sceneObject->childrenBegin();
	auto end = sceneObject->childrenEnd();
	while (it != end) {
		addObject(*it);
		it++;
	}
}

void cookie::SceneSectorManager::removeObject(const std::shared_ptr<SceneObject> &sceneObject) {
	objects.erase(std::find(objects.begin(), objects.end(), sceneObject));
	auto it = sceneObject->childrenBegin();
	auto end = sceneObject->childrenEnd();
	while (it != end) {
		removeObject(*it);
		it++;
	}
}

cookie::SceneSectorManager::~SceneSectorManager() = default;
