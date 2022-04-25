//
// Created by Antiufieiev Michael on 08.08.2021.
//

#include "Cube.hpp"
#include "Macro.h"

namespace cookie {

	Cube::Cube(float x, float y, float z) : SceneObject(STRCAT(BASE_DIR, "Car.fbx"), x, y, z) {
	}
}
