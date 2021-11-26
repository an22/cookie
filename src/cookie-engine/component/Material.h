//
// Created by Antiufieiev Michael on 12.08.2021.
//

#ifndef COOKIE_ENGINE_MATERIAL_H
#define COOKIE_ENGINE_MATERIAL_H

#include <vector>
#include <memory>
#include <string>
#include "Component.hpp"
#include <glm/vec3.hpp>

namespace cookie {

	struct Texture {
		enum class Type : char {
			SPECULAR = 's',
			DIFFUSE = 'd'
		};
		unsigned int id;
		std::string path;
		Type type;

		Texture() = default;
		Texture(unsigned int id, std::string path, Type type);
		Texture(unsigned int id, std::string path);
		Texture(const Texture &) = delete;
		Texture &operator=(const Texture &) = delete;
		Texture(Texture &&) noexcept;
	};

	class Material : public Component {
	public:

		std::string name;
		glm::vec3 diffuseColor;
		glm::vec3 specularColor;
		glm::vec3 ambientColor;
		glm::vec3 emissiveColor;
		glm::vec3 transparencyColor;

		float opacity = 1;
		float shininess = 0;
		float refraction = 1;

		std::vector<Texture> textures;

		Material() = default;
		Material(std::vector<Texture> &textures);
		Material(Material &&) noexcept;
		~Material() override = default;
		void onPreDraw();
	};
}

#endif //COOKIE_ENGINE_MATERIAL_H
