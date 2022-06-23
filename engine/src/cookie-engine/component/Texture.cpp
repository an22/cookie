//
// Created by Michael on 6/6/2022.
//

#include <algorithm>
#include "Texture.hpp"

namespace cookie {

	Texture::Texture(uint32_t id, std::string path, TextureType type) : id(id),
																 path(std::move(path)),
																 type(type) {
	}

	Texture::Texture(uint32_t id, std::string path) : id(id),
													  path(std::move(path)),
													  type(TextureType::DIFFUSE) {
	}

	Texture::Texture(Texture &&texture) noexcept: id(texture.id),
												  path(std::move(texture.path)),
												  type(texture.type) {
		texture.id = 0;
	}
}