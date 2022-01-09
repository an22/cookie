//
// Created by Antiufieiev Michael on 13.08.2021.
//

#ifndef COOKIE_ENGINE_TEXTUREPROCESSOR_HPP
#define COOKIE_ENGINE_TEXTUREPROCESSOR_HPP

#include <ktx.h>
#include "MeshStruct.h"
#include "Shader.hpp"

namespace cookie {
	class TextureProcessor {
	protected:
		virtual uint32_t generateAPITexture(ktxTexture *texture) = 0;
		virtual void bindTexturesToShader(const std::vector<Texture> &textures, const Shader &shader) = 0;
	public:
		virtual std::unique_ptr<Texture> readTextureAt(const std::string &path, Texture::Type type);

		virtual ~TextureProcessor() = default;
	};
}


#endif //COOKIE_ENGINE_TEXTUREPROCESSOR_HPP
