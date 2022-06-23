//
// Created by Michael on 6/15/2022.
//

#include <utility>

#include "PointsData.h"

namespace cookie {
	PointsData::PointsData(
			std::vector<glm::vec4> points,
			std::vector<uint32_t> indices
	) : points(std::move(points)),
		indices(std::move(indices)) {}
}