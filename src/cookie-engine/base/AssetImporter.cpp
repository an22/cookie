//
// Created by Antiufieiev Michael on 18.08.2021.
//

#include "AssetImporter.hpp"
#include "regex"

namespace cookie {

	std::vector<Texture> AssetImporter::loadMaterialTextures(
			aiMaterial *mat,
			aiTextureType type,
			Texture::Type assignType,
			const std::string &meshPath
	) {
		std::vector<Texture> textures;
		auto textureProcessor = CookieFactory::provideTextureProcessor();
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
			aiString path;
			mat->GetTexture(type, i, &path);
			std::string texturePath = std::string(path.C_Str());
			std::string materialPath = meshPath + '/' + texturePath;
			auto texture = textureProcessor->createTexture(materialPath);
			texture->type = assignType;
			textures.push_back(std::move(*texture.release()));
		}
		return textures;
	}

	std::unique_ptr<MeshData> AssetImporter::decodeMesh(
			const std::string &meshPath,
			const aiScene *scene,
			const aiMesh *mesh
	) {
		auto meshData = std::make_unique<MeshData>();
		meshData->vertices = loadVertices(scene, mesh);
		meshData->textures = loadMaterials(meshPath, scene, mesh);
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			auto &face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				meshData->indices.push_back(face.mIndices[j]);
		}
		return meshData;
	}

	std::vector<Vertex> AssetImporter::loadVertices(const aiScene *scene, const aiMesh *mesh) {
		std::vector<Vertex> vertices;
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			Vertex vertex{};
			auto &aiVertex = mesh->mVertices[i];
			vertex.position = glm::vec3(aiVertex.x, aiVertex.y, aiVertex.z);
			if (mesh->mNormals) {
				auto &aiNormal = mesh->mNormals[i];
				vertex.normal = glm::vec3(aiNormal.x, aiNormal.y, aiNormal.z);
			}
			if (mesh->mTextureCoords[0]) {
				auto &texCoord = mesh->mTextureCoords[0][i];
				vertex.texCoords = glm::vec2(texCoord.x, texCoord.y);
			} else {
				vertex.texCoords = glm::vec2(0.0f, 0.0f);
			}
			vertices.push_back(std::move(vertex));
		}
		return vertices;
	}

	//TODO add more materials support
	std::vector<Texture> AssetImporter::loadMaterials(
			const std::string &meshPath,
			const aiScene *scene,
			const aiMesh *mesh
	) {
		std::vector<Texture> textures;
		if (mesh->mMaterialIndex >= 0) {
			aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
			auto diffuseMaps = loadMaterialTextures(
					material,
					aiTextureType_DIFFUSE,
					Texture::Type::DIFFUSE,
					meshPath
			);
			std::move(diffuseMaps.begin(), diffuseMaps.end(), std::back_inserter(textures));
			std::vector<Texture> specularMaps = loadMaterialTextures(
					material,
					aiTextureType_SPECULAR,
					Texture::Type::SPECULAR,
					meshPath
			);
			std::move(specularMaps.begin(), specularMaps.end(), std::back_inserter(textures));
		}
		return textures;
	}

	std::vector<std::unique_ptr<MeshData>> AssetImporter::importMesh(const std::string &path) {
		Assimp::Importer importer;
		const aiScene *scene = importer.ReadFile(
				path.c_str(),
				aiProcess_CalcTangentSpace |
				aiProcess_Triangulate |
				aiProcess_FlipUVs
		);
		// If the import failed, report it
		if (!scene || !scene->HasMeshes()) {
			throw std::runtime_error("Can't import asset at " + path);
		}
		std::vector<std::unique_ptr<MeshData>> meshes;
		for (int i = 0; i < scene->mNumMeshes; ++i) {
			auto meshData = decodeMesh(path.substr(0, path.find_last_of('/')), scene, scene->mMeshes[i]);
			meshes.push_back(std::move(meshData));
		}
		return meshes;
	}
}
