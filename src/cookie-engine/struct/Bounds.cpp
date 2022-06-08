//
// Created by Michael on 6/2/2022.
//
#include "Bounds.hpp"
#include <limits>

namespace cookie {
	Bounds Bounds::transform(const glm::mat4 &transformation) {
		min = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), 1};
		max = {std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), 1};
		for (auto &point: points) {
			point = transformation * point;
			if (min.x > point.x) min.x = point.x;
			if (min.z > point.z) min.z = point.z;
			if (min.y > point.y) min.y = point.y;
			if (max.x < point.x) max.x = point.x;
			if (max.z < point.z) max.z = point.z;
			if (max.y < point.y) max.y = point.y;
		}
		return { min, max };
	}

	void Bounds::calculatePoints() {
		points[0] = min;
		points[1] = {max.x, min.y, min.z, 1};
		points[2] = {max.x, min.y, max.z, 1};
		points[3] = {min.x, min.y, max.z, 1};
		points[4] = {min.x, max.y, min.z, 1};
		points[5] = {max.x, max.y, min.z, 1};
		points[6] = max;
		points[7] = {min.x, max.y, max.z, 1};
	}

	Bounds::Bounds(const glm::vec4 &min, const glm::vec4 &max) : min(min), max(max), points(8) {
		calculatePoints();
	}

	Bounds::~Bounds() = default;

	Bounds::Bounds(const Bounds &bounds) = default;
}
