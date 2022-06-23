//
// Created by Michael on 6/6/2022.
//

#ifndef COOKIE_ENGINE_TEXTURE_HPP
#define COOKIE_ENGINE_TEXTURE_HPP

#include <string>
#include "TextureType.hpp"

namespace cookie {
	struct Texture {
		uint32_t id;
		std::string path;
		TextureType type;

		Texture(uint32_t id, std::string path, TextureType type);
		Texture(uint32_t id, std::string path);
		Texture(const Texture &) = delete;
		Texture &operator=(const Texture &) = delete;
		Texture(Texture &&) noexcept;
	};
}

#endif //COOKIE_ENGINE_TEXTURE_HPP
