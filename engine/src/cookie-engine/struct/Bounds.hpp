//
// Created by Michael on 6/1/2022.
//

#ifndef COOKIE_ENGINE_BOUNDS_HPP
#define COOKIE_ENGINE_BOUNDS_HPP

#include <glm/glm.hpp>
#include <vector>

namespace cookie {
	struct Bounds {
		constexpr static uint32_t indices[] = {
				//TOP
				0, 5, 1,
				0, 4, 5,
				//BACK
				3, 0, 2,
				2, 1, 3,
				//RIGHT
				0, 2, 7,
				2, 7, 4,
				//BOTTOM
				2, 3, 7,
				3, 6, 7,
				//LEFT
				6, 1, 5,
				6, 3, 1,
				//FRONT
				5, 4, 7,
				7, 5, 6
		};
		std::vector<glm::vec4> points;
		glm::vec4 min;
		glm::vec4 max;

		Bounds(const glm::vec4 &min, const glm::vec4 &max);
		Bounds(const Bounds &bounds);
		~Bounds();
		void calculatePoints();
		Bounds transform(const glm::mat4 &transformation);
	};
}

#endif //COOKIE_ENGINE_BOUNDS_HPP
