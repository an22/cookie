//
// Created by Antiufieiev Michael on 13.08.2021.
//

#include <stdexcept>
#include "TextureProcessor.hpp"

std::unique_ptr<cookie::Texture> cookie::TextureProcessor::readTextureAt(const std::string &path, Texture::Type type) {
	ktxTexture *texture;
	KTX_error_code errorCode = ktxTexture_CreateFromNamedFile(
			path.c_str(),
			KTX_TEXTURE_CREATE_NO_FLAGS,
			&texture
	);
	if (errorCode != KTX_SUCCESS) {
		throw std::runtime_error("Cannot open texture at " + path);
	}
	auto id = generateAPITexture(texture);
	ktxTexture_Destroy(texture);
	return std::make_unique<Texture>(id, path, type);
}
