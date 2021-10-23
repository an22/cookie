//
// Created by Antiufieiev Michael on 24.10.2021.
//

#ifndef COOKIE_ENGINE_UTILS_HPP
#define COOKIE_ENGINE_UTILS_HPP
#include <glm/glm.hpp>
#include <assimp/matrix4x4.h>

namespace cookie {

	class Utils {
	public:
		static glm::mat4 convertMatrix(const aiMatrix4x4 &aiMat);
	};
}


#endif //COOKIE_ENGINE_UTILS_HPP
