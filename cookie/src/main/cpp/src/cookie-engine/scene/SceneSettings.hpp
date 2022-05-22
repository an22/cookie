//
//  SceneSettings.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 06.07.2021.
//

#ifndef SceneSettings_hpp
#define SceneSettings_hpp

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace cookie {
	struct SceneSettings {
		unsigned int width, height;
		float aspectRatio{};
		glm::vec3 cameraPos;
		glm::mat4 perspectiveMx{};
		float FOV;
		float nearZ;
		float farZ;

		SceneSettings(unsigned int width, unsigned int height, float x, float y, float z, float fov, float nearZ, float farZ);
		void onWindowResized(unsigned int newWidth, unsigned int newHeight);
	};
}

#endif /* SceneSettings_hpp */

