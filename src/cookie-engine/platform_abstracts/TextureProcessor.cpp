//
// Created by Antiufieiev Michael on 13.08.2021.
//

#include "TextureProcessor.hpp"
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

stbi_uc *cookie::TextureProcessor::getFilePixels(const std::string &path,int &width, int &height, int& channelsInFile, int32_t channels) {
	stbi_uc* pixels = stbi_load(path.c_str(), &width, &height, &channelsInFile, channels);
	if (!pixels) {
		throw std::runtime_error("failed to load texture image!");
	}
	return pixels;
}
