//
//  SceneSettings.hpp
//  lighting-test
//
//  Created by Antiufieiev Michael on 06.07.2021.
//

#ifndef SceneSettings_hpp
#define SceneSettings_hpp

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#endif /* SceneSettings_hpp */

struct SceneSettings {
	float aspectRatio;
	glm::vec3 cameraPos;
	glm::mat4 perspectiveMx;
	
	
	SceneSettings(float x, float y, float z, GLFWwindow* window, float fov, float nearZ, float farZ) {
		cameraPos = glm::vec3(x,y,z);
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		aspectRatio = (float)width/(float)height;
		perspectiveMx = glm::perspective(fov, aspectRatio, nearZ, farZ);
	}
};
