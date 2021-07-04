//
//  BufferStorage.hpp
//  lighting-test
//
//  Created by Antiufieiev Michael on 01.07.2021.
//

#ifndef BufferStorage_hpp
#define BufferStorage_hpp
#include <GL/glew.h>

#endif /* BufferStorage_hpp */

struct BufferStorage {
	std::size_t arrayObjectsSize;
	std::size_t bufferObjectsSize;
	
	GLuint* vao;
	GLuint* vbo;
	
	BufferStorage(std::size_t arrayObjectsSize, std::size_t bufferObjectsSize) {
		this->arrayObjectsSize = arrayObjectsSize;
		this->bufferObjectsSize = bufferObjectsSize;
		vao = new GLuint[arrayObjectsSize];
		vbo = new GLuint[bufferObjectsSize];
	}
};
