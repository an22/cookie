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
		uint32_t width, height;
		float aspectRatio{};
		float FOV;
		float nearZ;
		float farZ;
		uint32_t lightsPerMesh;
		uint16_t objectsPerCell;
		uint32_t maxLights;
		uint32_t maxMeshes;
		glm::mat4 perspectiveMx{};
		glm::vec3 cameraPos;
		glm::ivec3 grid;

		SceneSettings(uint32_t width, uint32_t height, float x, float y, float z, float fov, float nearZ, float farZ);
		void onWindowResized(uint32_t newWidth, uint32_t newHeight);
	};
}

#endif /* SceneSettings_hpp */

