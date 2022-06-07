//
// Created by Michael on 4/25/2022.
//

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
	Bounds objBounds{};
	glm::ivec3 cell{};
	for (auto &obj: objects) {
		mesh = obj->getComponent<MeshComponent>();
		sectors = obj->getComponent<SectorComponent>();
		if (obj->getTransformation()->isChanged() && mesh != nullptr) {
			obj->getTransformation()->setIsChanged(false);
			sectors->clear();
			objBounds = mesh->getBounds();
			for (uint32_t x = floor(objBounds.min.x); x < (uint32_t) ceil(objBounds.max.x); x++) {
				for (uint32_t y = floor(objBounds.min.y); y < (uint32_t) ceil(objBounds.max.y); y++) {
					for (uint32_t z = floor(objBounds.min.z); z < (uint32_t) ceil(objBounds.max.z); y++) {
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

cookie::SceneSectorManager::~SceneSectorManager() = default;
