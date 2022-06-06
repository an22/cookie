//
// Created by Antiufieiev Michael on 12.08.2021.
//

#ifndef COOKIE_ENGINE_MATERIAL_H
#define COOKIE_ENGINE_MATERIAL_H

#include <vector>
#include <string>
#include <glm/vec4.hpp>

namespace cookie {

	class Texture;

	struct GPUMaterial {
		glm::vec4 baseColor;
		glm::vec4 emissiveColor;
		float roughness;
		float metallic = 0;
		float specular = 0.5f;
		float opacity = 1;
		bool doubleSided = false;

		GPUMaterial();
		GPUMaterial(
				const glm::vec4 &baseColor,
				const glm::vec4 &emissiveColor,
				float roughness,
				float metallic,
				float specular,
				float opacity,
				bool doubleSided
		);

		virtual ~GPUMaterial();
	};

	class Material : public GPUMaterial {
	public:

		std::string name;
		std::vector<Texture> textures;

		Material() = default;
		Material(
				std::string name,
				const glm::vec4 &baseColor,
				const glm::vec4 &emissiveColor,
				float roughness,
				float metallic,
				float specular,
				float opacity,
				bool doubleSided,
				std::vector<Texture> &textures
		) noexcept;
		Material(Material &&) noexcept;
		~Material() override;
		void onPreDraw();
	};
}

#endif //COOKIE_ENGINE_MATERIAL_H
