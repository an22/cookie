//
// Created by Michael on 6/1/2022.
//

#ifndef COOKIE_ENGINE_BOUNDS_HPP
#define COOKIE_ENGINE_BOUNDS_HPP

#include <glm/glm.hpp>
namespace cookie {
	struct Bounds {
		glm::vec4 points[8];
		glm::vec4 min;
		glm::vec4 max;

		Bounds();
		Bounds(const Bounds &bounds);
		~Bounds();
		void calculatePoints();
		void transform(const glm::mat4 &transformation);
	};
}

#endif //COOKIE_ENGINE_BOUNDS_HPP
