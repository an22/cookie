//
// Created by Antiufieiev Michael on 18.08.2021.
//

#ifndef COOKIE_ENGINE_ASSETIMPORTER_HPP
#define COOKIE_ENGINE_ASSETIMPORTER_HPP

#include "MeshStruct.h"
#include "SceneObject.hpp"
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

namespace cookie {
	class AssetImporter {
	private:

		inline static std::vector<std::shared_ptr<Material>> loadMaterials(
				const aiScene *scene,
				const std::string &meshPath
		);
		inline static std::vector<Texture> loadTexture(
				aiMaterial *mat,
				aiTextureType type,
				Texture::Type assignType,
				const std::string &meshPath
		);
		inline static void decodeSceneRecursively(
				const aiScene* rootScene,
				const aiNode *sceneNode,
				const std::vector<std::shared_ptr<Material>>& materials,
				SceneObject &sceneObject
		);
		inline static void decodeMesh(
				const aiMesh *mesh,
				MeshData &target
		);
		inline static std::vector<Texture> loadTextures(
				aiMaterial *mesh,
				const std::string &meshPath
		);
		inline static std::vector<Vertex> loadVertices(const aiMesh *mesh);
	public:
		static void importMesh(SceneObject &root, const std::string &path);
	};
}


#endif //COOKIE_ENGINE_ASSETIMPORTER_HPP
