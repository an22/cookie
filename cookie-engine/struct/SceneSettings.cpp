//
//  SceneSettings.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 06.08.2021.
//

#include "SceneSettings.hpp"

namespace cookie {
SceneSettings::SceneSettings(uint32_t width,uint32_t height, float x, float y, float z, float fov, float nearZ, float farZ) {
	this->width = width;
	this->height = height;
	cameraPos = glm::vec3(x,y,z);
	aspectRatio = (float)width/(float)height;
	perspectiveMx = glm::perspective(fov, aspectRatio, nearZ, farZ);
}
}
