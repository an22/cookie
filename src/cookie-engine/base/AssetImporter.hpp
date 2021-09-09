//
// Created by Antiufieiev Michael on 18.08.2021.
//

#ifndef COOKIE_ENGINE_ASSETIMPORTER_HPP
#define COOKIE_ENGINE_ASSETIMPORTER_HPP

#include "MeshStruct.h"
#include "TextureProcessor.hpp"
#include "CookieFactory.hpp"
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace cookie {
	class AssetImporter {
	private:

		static std::vector<Texture> loadMaterialTextures(
				aiMaterial *mat,
				aiTextureType type,
				Texture::Type assignType,
				const std::string &meshPath
		);
		static std::unique_ptr<MeshData> decodeMesh(
				const std::string &meshPath,
				const aiScene *scene,
				const aiMesh *mesh
		);
		static std::vector<Texture> loadMaterials(
				const std::string &meshPath,
				const aiScene *scene,
				const aiMesh *mesh
		);
		static void processNode(
				std::vector<std::unique_ptr<MeshData>> &meshes,
				const std::string &path,
				aiNode *node,
				const aiScene *scene
		);
		static std::vector<Vertex> loadVertices(const aiScene *scene, const aiMesh *mesh);
	public:
		static std::vector<std::unique_ptr<MeshData>> importMesh(const std::string &path);
	};
}


#endif //COOKIE_ENGINE_ASSETIMPORTER_HPP
