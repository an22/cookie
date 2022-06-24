//
// Created by Antiufieiev Michael on 13.08.2021.
//

#ifndef COOKIE_ENGINE_EGLTEXTUREPROCESSOR_HPP
#define COOKIE_ENGINE_EGLTEXTUREPROCESSOR_HPP

#if COOKIE_EGL

#include "TextureProcessor.hpp"

namespace cookie {
	class EGLTextureProcessor : public cookie::TextureProcessor {
		uint32_t generateAPITexture(ktxTexture *texture) override;
		void bindTexturesToShader(
				const std::vector<cookie::Texture> &textures,
				const cookie::Shader &shader
		) override;
	};
}

#endif
#endif //COOKIE_ENGINE_EGLTEXTUREPROCESSOR_HPP
