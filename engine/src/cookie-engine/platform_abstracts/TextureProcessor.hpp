//
// Created by Antiufieiev Michael on 13.08.2021.
//

#ifndef COOKIE_ENGINE_TEXTUREPROCESSOR_HPP
#define COOKIE_ENGINE_TEXTUREPROCESSOR_HPP

#include "ktx/ktx.h"
#include <vector>
#include <memory>
#include "TextureType.hpp"

namespace cookie {

	class Shader;
	class Texture;

	class TextureProcessor {
	protected:
		virtual uint32_t generateAPITexture(ktxTexture *texture) = 0;
		virtual void bindTexturesToShader(const std::vector<Texture> &textures, const Shader &shader) = 0;
	public:
		virtual std::unique_ptr<Texture> readTextureAt(const std::string &path, TextureType type);

		TextureProcessor();
		virtual ~TextureProcessor();
	};
}

#endif //COOKIE_ENGINE_TEXTUREPROCESSOR_HPP
