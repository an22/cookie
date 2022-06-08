//
// Created by Michael on 6/1/2022.
//

#ifndef COOKIE_ENGINE_BOUNDS_HPP
#define COOKIE_ENGINE_BOUNDS_HPP

#include <glm/glm.hpp>
#include <vector>

namespace cookie {
	struct Bounds {
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
