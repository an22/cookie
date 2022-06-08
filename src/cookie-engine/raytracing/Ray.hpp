//
// Created by Michael on 4/25/2022.
//

#ifndef COOKIE_RAY_HPP
#define COOKIE_RAY_HPP

#include <glm/glm.hpp>

class Ray {
private:
	glm::vec3 from;
	glm::vec3 dir;
public:
	Ray(const glm::vec3 &from, const glm::vec3 &to);
	[[nodiscard]] const glm::vec3 &getFrom() const;
	void setFrom(const glm::vec3 &from);
	[[nodiscard]] const glm::vec3 &getDir() const;
	void setDir(const glm::vec3 &to);
};

#endif //COOKIE_RAY_HPP
