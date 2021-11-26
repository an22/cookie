//
// Created by Antiufieiev Michael on 12.08.2021.
//

#include "Material.h"
#include "Cookie.hpp"

namespace cookie {
	void Material::onPreDraw() {
	}

	Material::Material(
			std::vector<Texture> &textures
	) : textures(std::move(textures)) {
	}

	Material::Material(Material &&mat) noexcept: textures(std::move(mat.textures)),
												 name(std::move(mat.name)),
												 diffuseColor(mat.diffuseColor),
												 specularColor(mat.specularColor),
												 ambientColor(mat.ambientColor),
												 emissiveColor(mat.emissiveColor),
												 transparencyColor(mat.transparencyColor),
												 opacity(mat.opacity),
												 shininess(mat.shininess),
												 refraction(mat.refraction) {
	}

	Texture::Texture(unsigned int id, std::string path, Type type) : id(id),
																	 path(std::move(path)),
																	 type(type) {
	}

	Texture::Texture(unsigned int id, std::string path) : id(id),
														  path(std::move(path)),
														  type(Type::DIFFUSE) {
	}

	Texture::Texture(Texture &&texture) noexcept: id(texture.id),
												  path(std::move(texture.path)),
												  type(texture.type) {
		texture.id = 0;
	}
}
