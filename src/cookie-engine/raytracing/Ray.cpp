//
// Created by Michael on 4/25/2022.
//

#include "Ray.hpp"

Ray::Ray(const glm::vec3 &from, const glm::vec3 &to) : from(from), dir(to) {}

const glm::vec3 &Ray::getFrom() const {
	return from;
}

void Ray::setFrom(const glm::vec3 &from) {
	Ray::from = from;
}

const glm::vec3 &Ray::getDir() const {
	return dir;
}

void Ray::setDir(const glm::vec3 &to) {
	Ray::dir = to;
}
