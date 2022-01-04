//
// Created by Antiufieiev Michael on 13.08.2021.
//

#ifndef COOKIE_ENGINE_TEXTUREPROCESSOR_HPP
#define COOKIE_ENGINE_TEXTUREPROCESSOR_HPP

#include "MeshStruct.h"
#include "Shader.hpp"

namespace cookie {
	class TextureProcessor {
	public:
		virtual void  fillTexture(const std::string &path, Texture& target) = 0;
		virtual void bindTexturesToShader(const std::vector<Texture>& textures, const Shader& shader) = 0;
		unsigned char *getFilePixels(const std::string &path, int &width, int &height, int& channelsInFile,int32_t channels);

		virtual ~TextureProcessor() = default;
	};
}


#endif //COOKIE_ENGINE_TEXTUREPROCESSOR_HPP
