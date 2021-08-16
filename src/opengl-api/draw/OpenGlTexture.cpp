//
// Created by Antiufieiev Michael on 13.08.2021.
//

#include "OpenGlTexture.hpp"
#include <GL/glew.h>

std::unique_ptr<cookie::Texture> OpenGLTexture::createTexture(const std::string &path, int32_t channels) {
	int width, height, channelsInFile;
	unsigned char *pixels = cookie::TextureProcessor::getFilePixels(path, width, height, channelsInFile, channels);
	if (channelsInFile != channels) {
		free(pixels);
		throw std::runtime_error(
				"Image at " + path + " contains " + std::to_string(channelsInFile) + " sections, but " +
				std::to_string(channelsInFile) + "was expected"
		);
	}
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	free(pixels);
	return std::make_unique<cookie::Texture>(
			textureID,
			channelsInFile
	);
}
