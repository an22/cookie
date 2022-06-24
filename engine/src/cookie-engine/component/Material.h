//
// Created by Antiufieiev Michael on 12.08.2021.
//

#ifndef COOKIE_ENGINE_MATERIAL_H
#define COOKIE_ENGINE_MATERIAL_H

#include <vector>
#include <string>
#include <glm/vec4.hpp>
#include <memory>

namespace cookie {

	class Texture;
	class Shader;

	struct GPUMaterial {
		glm::vec4 baseColor;
		glm::vec4 emissiveColor;
		float roughness;
		float metallic = 0;
		float specular = 0.5f;
		float opacity = 1;
		bool doubleSided = false;

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
		std::shared_ptr<Shader> shader;
		std::vector<Texture> textures;

		Material(
				std::string name,
				const glm::vec4 &baseColor,
				const glm::vec4 &emissiveColor,
				float roughness,
				float metallic,
				float specular,
				float opacity,
				bool doubleSided,
				std::vector<Texture> &textures,
				std::shared_ptr<Shader> shader
		) noexcept;
		Material(Material &&) noexcept;
		~Material() override;
		virtual void onPreDraw();
		virtual void onPostDraw();
		void enableShader() const;
		void disableShader() const;
	};
}

#endif //COOKIE_ENGINE_MATERIAL_H
