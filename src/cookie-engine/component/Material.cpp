//
// Created by Antiufieiev Michael on 12.08.2021.
//

#include "Material.h"

#include <utility>
#include "Texture.hpp"
#include "Cookie.hpp"

namespace cookie {
	void Material::onPreDraw() {
	}

	Material::Material(
			std::string name,
			const glm::vec4 &baseColor,
			const glm::vec4 &emissiveColor,
			float roughness,
			float metallic,
			float specular,
			float opacity,
			bool doubleSided,
			std::vector<Texture> &textures
	) noexcept: GPUMaterial(
			baseColor,
			emissiveColor,
			roughness,
			metallic,
			specular,
			opacity,
			doubleSided
	), name(std::move(name)), textures(std::move(textures)) {
	}

	Material::Material(Material &&mat) noexcept:
			GPUMaterial(
					mat.baseColor,
					mat.emissiveColor,
					mat.roughness,
					mat.metallic,
					mat.specular,
					mat.opacity,
					mat.doubleSided
			),
			textures(std::move(mat.textures)),
			name(std::move(mat.name)) {

	}

	Material::~Material() = default;

	GPUMaterial::GPUMaterial(const glm::vec4 &baseColor,
							 const glm::vec4 &emissiveColor,
							 float roughness,
							 float metallic,
							 float specular,
							 float opacity,
							 bool doubleSided)
			: baseColor(baseColor), emissiveColor(emissiveColor), roughness(roughness),
			  metallic(metallic), specular(specular), opacity(opacity),
			  doubleSided(doubleSided) {}

	GPUMaterial::~GPUMaterial() = default;

	GPUMaterial::GPUMaterial() = default;
}
