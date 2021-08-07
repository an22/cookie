//
//  OpenGLShader.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#ifndef OpenGLShader_hpp
#define OpenGLShader_hpp
#include <string>
#include "Shader.hpp"

class OpenGLShader : public cookie::Shader {
public:
	OpenGLShader(const std::string & vertexPath, const std::string & fragmentPath);
	void use() override;
	void setBool(const std::string &name, bool value) const override;
	void setInt(const std::string &name, int32_t value) const override;
	void setFloat(const std::string &name, float value) const override;
	~OpenGLShader() override = default;
};

#endif /* OpenGLShader_hpp */
