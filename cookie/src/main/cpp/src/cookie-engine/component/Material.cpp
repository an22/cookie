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

	Material::Material(Material &&mat) noexcept:
			GPUMaterial(
					mat.diffuseColor,
					mat.specularColor,
					mat.ambientColor,
					mat.emissiveColor,
					mat.transparencyColor,
					mat.opacity,
					mat.shininess,
					mat.refraction
			),
			textures(std::move(mat.textures)),
			name(std::move(mat.name)) {

	}

	Texture::Texture(uint32_t id, std::string path, Type type) : id(id),
																	 path(std::move(path)),
																	 type(type) {
	}

	Texture::Texture(uint32_t id, std::string path) : id(id),
														  path(std::move(path)),
														  type(Type::DIFFUSE) {
	}

	Texture::Texture(Texture &&texture) noexcept: id(texture.id),
												  path(std::move(texture.path)),
												  type(texture.type) {
		texture.id = 0;
	}

	GPUMaterial::GPUMaterial(const glm::vec3 &diffuseColor, const glm::vec3 &specularColor,
							 const glm::vec3 &ambientColor, const glm::vec3 &emissiveColor,
							 const glm::vec3 &transparencyColor, float opacity, float shininess, float refraction)
			: diffuseColor(diffuseColor), specularColor(specularColor), ambientColor(ambientColor),
			  emissiveColor(emissiveColor), transparencyColor(transparencyColor), opacity(opacity),
			  shininess(shininess), refraction(refraction) {}

	GPUMaterial::GPUMaterial() = default;
}
