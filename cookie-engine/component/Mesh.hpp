//
//  Mesh.hpp
//  lighting-test
//
//  Created by Antiufieiev Michael on 28.07.2021.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Component.h"
#include "BufferStorage.hpp"
#include "Shader.hpp"

namespace cookie {

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

struct Texture {
	uint32_t id;
	std::string type;
};

class Mesh : public Component {
private:
	
	BufferStorage bufferStorage; //TODO provide storage
	
	void setupMesh() {
		//TODO
	}
	
public:
	// mesh data
	std::vector<Vertex>   vertices;
	std::vector<uint32_t> indices;
	std::vector<Texture>  textures;
	
	Mesh(std::vector<Vertex> &vertices, std::vector<uint32_t> &indices, std::vector<Texture> &textures) {
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
		setupMesh();
	}
	
	virtual ~Mesh() {}
	
	void draw(Shader &shader) {
		//TODO draw mesh
	}
};

}

#endif /* Mesh_hpp */
