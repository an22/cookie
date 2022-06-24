//
//  SceneSettings.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 06.08.2021.
//

#include "SceneSettings.hpp"

namespace cookie {
	SceneSettings::SceneSettings(
			uint32_t width,
			uint32_t height,
			float x,
			float y,
			float z,
			float fov,
			float nearZ,
			float farZ
	) : width(width),
		height(height),
		cameraPos(glm::vec3(x, y, z)),
		FOV(fov),
		nearZ(nearZ),
		farZ(farZ),
		aspectRatio(static_cast<float>(width) / static_cast<float>(height)),
		perspectiveMx(glm::perspective(fov, aspectRatio, nearZ, farZ)) {
	}

	void SceneSettings::onWindowResized(uint32_t newWidth, uint32_t newHeight) {
		width = newWidth;
		height = newHeight;
		aspectRatio = static_cast<float>(newWidth) / static_cast<float>(newHeight);
		perspectiveMx = glm::perspective(FOV, aspectRatio, nearZ, farZ);
	}
}
