//
//  Shader.hpp
//  lighting-test
//
//  Created by Antiufieiev Michael on 28.07.2021.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader {
public:
	// the program ID
	unsigned int ID;
	
	// constructor reads and builds the shader
	Shader(const std::string & vertexPath, const std::string & fragmentPath);
	
	virtual ~Shader();
	// use/activate the shader
	virtual void use();
	// utility uniform functions
	virtual void setBool(const std::string &name, bool value) const;
	virtual void setInt(const std::string &name, int value) const;
	virtual void setFloat(const std::string &name, float value) const;
};

#endif /* Shader_hpp */
