//
// Created by Antiufieiev Michael on 13.08.2021.
//

#ifndef COOKIE_ENGINE_OPENGLTEXTUREPROCESSOR_HPP
#define COOKIE_ENGINE_OPENGLTEXTUREPROCESSOR_HPP

#if COOKIE_OPENGL

#include "TextureProcessor.hpp"

namespace cookie {
	class OpenGLTextureProcessor : public cookie::TextureProcessor {
		uint32_t generateAPITexture(ktxTexture *texture) override;
		void bindTexturesToShader(
				const std::vector<cookie::Texture> &textures,
				const cookie::Shader &shader
		) override;
	};
}

#endif
#endif //COOKIE_ENGINE_OPENGLTEXTUREPROCESSOR_HPP
