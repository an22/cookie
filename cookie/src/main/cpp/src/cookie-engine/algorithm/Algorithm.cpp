//
// Created by Michael on 4/25/2022.
//

#include "Algorithm.hpp"

glm::i32vec3 cookie::nextBox(const glm::vec3 &at) {
	return glm::i32vec3(floorf(at.x), floorf(at.y), floorf(at.z));
}