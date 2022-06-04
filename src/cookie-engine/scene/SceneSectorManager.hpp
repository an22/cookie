//
// Created by Michael on 4/25/2022.
//

#ifndef COOKIE_SCENESECTORMANAGER_HPP
#define COOKIE_SCENESECTORMANAGER_HPP

#include <unordered_map>
#include <glm.hpp>
#include <glm/gtx/hash.hpp>
#include <vector>
#include "Sector.hpp"
#include "Ray.hpp"
#include "Bounds.hpp"
#include "SceneObject.hpp"

namespace cookie {
	class SceneSectorManager {
	private:
		Bounds bounds;
		std::vector<std::shared_ptr<SceneObject>> objects;
		std::unordered_map<glm::ivec3, std::shared_ptr<Sector>, std::hash<glm::ivec3>> sectorMap;
	public:
		SceneSectorManager(float sectorSize, const Bounds &bounds);
		void update();
	};
}

#endif //COOKIE_SCENESECTORMANAGER_HPP
