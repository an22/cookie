//
//  SceneSettings.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 06.08.2021.
//

#include "SceneSettings.hpp"

namespace cookie {
	SceneSettings::SceneSettings(
			unsigned int width,
			unsigned int height,
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
		farZ(farZ) {
		onWindowResized(width, height);
	}

	void SceneSettings::onWindowResized(unsigned int newWidth, unsigned int newHeight) {
		width = newWidth;
		height = newHeight;
		aspectRatio = (float) newWidth / (float) newHeight;
		perspectiveMx = glm::perspective(FOV, aspectRatio, nearZ, farZ);
	}
}
