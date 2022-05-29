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

namespace cookie {
	class SceneSectorManager {
	private:
		float sectorSize;
		glm::vec4 bounds;
	public:
		std::unordered_map<glm::i32vec3, cookie::Sector, std::hash<glm::i32vec3>> sectorMap;
		SceneSectorManager(float sectorSize, const glm::vec4 &bounds);
	};
}

#endif //COOKIE_SCENESECTORMANAGER_HPP
