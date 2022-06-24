//
// Created by Michael on 6/15/2022.
//

#ifndef COOKIE_ENGINE_POINTSDATA_H
#define COOKIE_ENGINE_POINTSDATA_H

#include <vector>
#include <glm/vec4.hpp>

namespace cookie {
	struct PointsData {
		std::vector<glm::vec4> points;
		std::vector<uint32_t> indices;

		PointsData(std::vector<glm::vec4> points, std::vector<uint32_t> indices);
	};
}

#endif //COOKIE_ENGINE_POINTSDATA_H
