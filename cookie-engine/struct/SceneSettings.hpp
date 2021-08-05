//
//  SceneSettings.hpp
//  lighting-test
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
	float aspectRatio;
	glm::vec3 cameraPos;
	glm::mat4 perspectiveMx;
	
	
	SceneSettings(uint32_t width,uint32_t height, float x, float y, float z, float fov, float nearZ, float farZ);
};
}

#endif /* SceneSettings_hpp */

