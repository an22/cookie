//
// Created by Antiufieiev Michael on 13.08.2021.
//

#ifndef COOKIE_ENGINE_OPENGLTEXTURE_HPP
#define COOKIE_ENGINE_OPENGLTEXTURE_HPP

#include "TextureProcessor.hpp"

class OpenGLTexture : public cookie::TextureProcessor {
	std::unique_ptr<cookie::Texture> createTexture(const std::string &path, int32_t channels) override;
};


#endif //COOKIE_ENGINE_OPENGLTEXTURE_HPP
