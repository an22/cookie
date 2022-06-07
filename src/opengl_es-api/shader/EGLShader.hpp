//
//  EGLShader.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#ifndef EGLShader_hpp
#define EGLShader_hpp

#if COOKIE_EGL

#include <string>
#include "platform_abstracts/Shader.hpp"
#include "EGLErrorHandler.hpp"

namespace cookie {
	class EGLShader : public cookie::Shader {
	public:
		EGLShader(const std::string &vertexPath, const std::string &fragmentPath);
		explicit EGLShader(const std::string &computePath);
		~EGLShader() override = default;
		static GLuint loadShaderFrom(const std::string &path, GLenum shaderType);
		void use() override;
		void setBool(const std::string &name, bool value) const override;
		void setInt(const std::string &name, int32_t value) const override;
		void setFloat(const std::string &name, float value) const override;
		void setMatrix4(const std::string &name, const glm::mat4 &matrix) const override;
	};
}

#endif
#endif /* EGLShader_hpp */
