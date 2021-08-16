//
// Created by Antiufieiev Michael on 08.08.2021.
//

#include "Cube.hpp"
#include <vector>

namespace cookie {

	Cube::Cube(float x, float y, float z) : SceneObject(x, y, z) {
		addComponent<Mesh>(std::make_unique<Mesh>("/Users/antiufieievmichael/Guides/cookie-engine/mesh.obj"));
		auto shader = CookieFactory::provideShader(
				"/Users/antiufieievmichael/Guides/cookie-engine/src/cookie-engine/shader/vertex/vertex.glsl",
				"/Users/antiufieievmichael/Guides/cookie-engine/src/cookie-engine/shader/fragment/fragment.glsl"
		);
		addComponent<Shader>(std::move(shader));
	}
}
