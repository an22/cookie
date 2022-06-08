//
// Created by Antiufieiev Michael on 13.08.2021.
//
#include "config.hpp"

#if COOKIE_OPENGL

#include <GL/glew.h>
#include <stdexcept>
#include "OpenGLTextureProcessor.hpp"
#include "Texture.hpp"

namespace cookie {
	void OpenGLTextureProcessor::bindTexturesToShader(
			const std::vector<cookie::Texture> &textures,
			const cookie::Shader &shader
	) {
		std::string name;
		std::string number;
		unsigned int specularCount = 0;
		unsigned int diffuseCount = 0;
		for (unsigned int i = 0; i < textures.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
			// retrieve texture number (the N in diffuse_textureN)
			const auto &texture = textures[i];
			switch (texture.type) {
				case cookie::TextureType::SPECULAR:
					name = "specularTxr";
					number = std::to_string(++specularCount);
					break;
				case cookie::TextureType::DIFFUSE:
					name = "diffuseTxr";
					number = std::to_string(++diffuseCount);
					break;
			}
			glBindTexture(GL_TEXTURE_2D, texture.id);
		}
		glActiveTexture(GL_TEXTURE0);
	}

	uint32_t OpenGLTextureProcessor::generateAPITexture(ktxTexture *texture) {
		GLuint textureID;
		glGenTextures(1, &textureID);
		GLenum trgt, error;
		ktxResult errorCode = ktxTexture_GLUpload(texture, &textureID, &trgt, &error);
		if (errorCode != KTX_SUCCESS) {
			throw std::runtime_error("Cannot upload texture");
		}
		ktxTexture_Destroy(texture);
		return textureID;
	}
}

#endif
