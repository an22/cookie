//
// Created by Antiufieiev Michael on 24.10.2021.
//

#include "Utils.hpp"

glm::mat4 cookie::Utils::convertMatrix(const aiMatrix4x4 &aiMat) {
	return {
			aiMat.a1, aiMat.b1, aiMat.c1, aiMat.d1,
			aiMat.a2, aiMat.b2, aiMat.c2, aiMat.d2,
			aiMat.a3, aiMat.b3, aiMat.c3, aiMat.d3,
			aiMat.a4, aiMat.b4, aiMat.c4, aiMat.d4
	};
}
