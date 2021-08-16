//
// Created by Antiufieiev Michael on 13.08.2021.
//

#ifndef COOKIE_ENGINE_TEXTUREPROCESSOR_HPP
#define COOKIE_ENGINE_TEXTUREPROCESSOR_HPP

#include "MeshStruct.h"
#include <memory>

namespace cookie {
	class TextureProcessor {
	public:
		virtual std::unique_ptr<cookie::Texture> createTexture(const std::string &path, int32_t channels) = 0;
		unsigned char *getFilePixels(const std::string &path, int &width, int &height, int& channelsInFile,int32_t channels);

	};
}


#endif //COOKIE_ENGINE_TEXTUREPROCESSOR_HPP
