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
#include "Shader.hpp"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

struct Texture {
	unsigned int id;
	std::string type;
};

class Mesh : Component {
public:
	// mesh data
	std::vector<Vertex>       vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture>      textures;
	
	Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, std::vector<Texture> &textures);

	void draw(Shader &shader);
	
	virtual ~Mesh();
private:
	//  render data
	unsigned int VAO, VBO, EBO;
	
	void setupMesh();
};


#endif /* Mesh_hpp */
