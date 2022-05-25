//
// Created by Antiufieiev Michael on 08.08.2021.
//

#include <matrix_transform.hpp>
#include "Cube.hpp"
#include "Macro.h"

namespace cookie {

	Cube::Cube(float x, float y, float z) : SceneObject("adamHead.gltf", glm::vec3(x, y, z)) {
	}
}
