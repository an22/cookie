//
// Created by Michael on 4/25/2022.
//

#include "SceneSectorManager.hpp"
#include "Algorithm.hpp"

cookie::SceneSectorManager::SceneSectorManager(float sectorSize, const glm::vec4 &bounds)
		: sectorSize(sectorSize), sectorMap(), bounds(bounds) {

}
