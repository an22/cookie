//
// Created by Antiufieiev Michael on 13.08.2021.
//

#include "OpenGLTextureProcessor.hpp"
#include <GL/glew.h>

std::unique_ptr<cookie::Texture> OpenGLTextureProcessor::createTexture(const std::string &path) {
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
	return std::make_unique<cookie::Texture>(
			textureID,
			path
	);
}
