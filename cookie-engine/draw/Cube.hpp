//
//  Cube.hpp
//  lighting-test
//
//  Created by Antiufieiev Michael on 06.07.2021.
//

#ifndef Cube_hpp
#define Cube_hpp

#include <stdio.h>
#include "SceneObject.hpp"

namespace cookie {
class Cube : public SceneObject {
	
public:
	Cube(float x, float y, float z) : SceneObject(x,y,z) {
	}
	static const int meshSize = 108;
	
	~Cube() {
		
	}
	
	static float* genMesh() {
		float* mesh = new float[meshSize] {
				-1.0f, 1.0f, -1.0f, -1.0f,
				-1.0f, -1.0f, 1.0f, -1.0f,
				-1.0f, 1.0f, -1.0f, -1.0f,
				1.0f, 1.0f, -1.0f, -1.0f,
				1.0f, -1.0f, 1.0f, -1.0f,
				-1.0f, 1.0f, -1.0f, 1.0f,
				1.0f, 1.0f, -1.0f, 1.0f,
				-1.0f, 1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, -1.0f,
				1.0f, -1.0f, 1.0f, -1.0f,
				-1.0f, 1.0f, 1.0f, 1.0f,
				1.0f, -1.0f, -1.0f, 1.0f,
				-1.0f, 1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, -1.0f, -1.0f,
				1.0f, -1.0f, -1.0f, -1.0f,
				-1.0f, 1.0f, 1.0f, -1.0f,
				-1.0f, -1.0f, -1.0f, 1.0f,
				-1.0f, -1.0f, 1.0f, 1.0f,
				-1.0f, -1.0f, 1.0f, 1.0f,
				-1.0f, 1.0f, 1.0f, -1.0f,
				-1.0f, 1.0f, -1.0f, -1.0f,
				-1.0f, -1.0f, -1.0f, -1.0f,
				-1.0f, 1.0f, -1.0f, 1.0f,
				-1.0f, 1.0f, 1.0f, -1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, -1.0f, 1.0f,
				1.0f, -1.0f, 1.0f, -1.0f
		};
		return mesh;
	}
};
}

#endif /* Cube_hpp */
