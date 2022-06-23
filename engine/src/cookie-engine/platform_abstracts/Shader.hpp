//
//  Shader.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 28.07.2021.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <string>
#include <glm/glm.hpp>
#include <Component.hpp>

namespace cookie {

	class Shader {
	public:
		uint32_t id;

		explicit Shader(uint32_t id);
		virtual ~Shader() = default;
		// use/activate the shader
		virtual void use() = 0;
		virtual void disable() = 0;
		// utility uniform functions
		virtual void setBool(const std::string &name, bool value) const = 0;
		virtual void setInt(const std::string &name, int32_t value) const = 0;
		virtual void setFloat(const std::string &name, float value) const = 0;
		virtual void setMatrix4(const std::string &name, const glm::mat4 &matrix) const = 0;
		//TODO add more utility functions
	};
}
#endif /* Shader_hpp */
