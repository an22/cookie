//
//  OpenGLShader.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#ifndef OpenGLShader_hpp
#define OpenGLShader_hpp

#include <string>
#include <gl/glew.h>
#include "platform_abstracts/Shader.hpp"
#include "GLErrorHandler.hpp"

class OpenGLShader : public cookie::Shader {
public:
	OpenGLShader(const std::string &vertexPath, const std::string &fragmentPath);
	~OpenGLShader() override = default;

	static GLuint loadShaderFrom(const std::string &path, GLenum shaderType);

	void use() override;
	void setBool(const std::string &name, bool value) const override;
	void setInt(const std::string &name, int32_t value) const override;
	void setFloat(const std::string &name, float value) const override;
	void setMatrix4(const std::string &name, const glm::mat4 &matrix) const override;
};

#endif /* OpenGLShader_hpp */
