//
// Created by Antiufieiev Michael on 13.08.2021.
//

#ifndef COOKIE_ENGINE_OPENGLTEXTUREPROCESSOR_HPP
#define COOKIE_ENGINE_OPENGLTEXTUREPROCESSOR_HPP

#include "TextureProcessor.hpp"

class OpenGLTextureProcessor : public cookie::TextureProcessor {
	std::unique_ptr<cookie::Texture> createTexture(const std::string &path) override;
};


#endif //COOKIE_ENGINE_OPENGLTEXTUREPROCESSOR_HPP
