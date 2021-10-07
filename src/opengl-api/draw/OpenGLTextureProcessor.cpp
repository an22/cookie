//
// Created by Antiufieiev Michael on 13.08.2021.
//

#include "OpenGLTextureProcessor.hpp"
#include <GL/glew.h>

void OpenGLTextureProcessor::fillTexture(const std::string &path, cookie::Texture &target) {
	int width, height, channelsInFile;
	unsigned char *pixels = cookie::TextureProcessor::getFilePixels(
			path,
			width,
			height,
			channelsInFile,
			0
	);
	GLuint textureID;
	if (pixels) {
		GLint format = 0;
		if (channelsInFile == 1)
			format = GL_RED;
		else if (channelsInFile == 3)
			format = GL_RGB;
		else if (channelsInFile == 4)
			format = GL_RGBA;

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		free(pixels);
	} else {
		throw std::runtime_error("Cannot process image at " + path);
	}
	target.id = textureID;
	target.path = path;
}

void OpenGLTextureProcessor::bindTexturesToShader(const std::vector<cookie::Texture> &textures,
												  const cookie::Shader &shader) {
	std::string name;
	std::string number;
	unsigned int specularCount = 0;
	unsigned int diffuseCount = 0;
	for (unsigned int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		const auto &texture = textures[i];
		switch (texture.type) {
			case cookie::Texture::Type::SPECULAR:
				name = "specular";
				number = std::to_string(++specularCount);
				break;
			case cookie::Texture::Type::DIFFUSE:
				name = "diffuse";
				number = std::to_string(++diffuseCount);
				break;
		}
		name += number;
		shader.setFloat(name, i);
		glBindTexture(GL_TEXTURE_2D, texture.id);
	}
	glActiveTexture(GL_TEXTURE0);
}
