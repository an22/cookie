//
// Created by Michael on 6/2/2022.
//
#include "Bounds.hpp"
#include <limits>

namespace cookie {
	Bounds Bounds::transform(const glm::mat4 &transformation) {
		min = {
				std::numeric_limits<float>::max(),
				std::numeric_limits<float>::max(),
				std::numeric_limits<float>::max(),
				1
		};
		max = {
				std::numeric_limits<float>::min(),
				std::numeric_limits<float>::min(),
				std::numeric_limits<float>::min(),
				1
		};
		glm::vec4 transformedPoint;
		for (auto &point: points) {
			transformedPoint = transformation * point;
			if (min.x > transformedPoint.x) { min.x = transformedPoint.x; }
			if (min.z > transformedPoint.z) { min.z = transformedPoint.z; }
			if (min.y > transformedPoint.y) { min.y = transformedPoint.y; }
			if (max.x < transformedPoint.x) { max.x = transformedPoint.x; }
			if (max.z < transformedPoint.z) { max.z = transformedPoint.z; }
			if (max.y < transformedPoint.y) { max.y = transformedPoint.y; }
		}
		return {min, max};
	}

//1 - - - 0
//| \     | \
//|   5 - - - 4
//|   |   |   |
//3 - | - 2   |
//  \ |     \ |
//    6 - - - 7
	void Bounds::calculatePoints() {
		points[3] = min;
		points[2] = {max.x, min.y, min.z, 1};
		points[7] = {max.x, min.y, max.z, 1};
		points[6] = {min.x, min.y, max.z, 1};
		points[1] = {min.x, max.y, min.z, 1};
		points[0] = {max.x, max.y, min.z, 1};
		points[4] = max;
		points[5] = {min.x, max.y, max.z, 1};
	}

	Bounds::Bounds(const glm::vec4 &min, const glm::vec4 &max) : min(min), max(max), points(8) {
		calculatePoints();
	}

	Bounds::~Bounds() = default;

	Bounds::Bounds(const Bounds &bounds) = default;
}
