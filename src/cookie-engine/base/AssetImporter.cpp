//
// Created by Antiufieiev Michael on 18.08.2021.
//

#include "AssetImporter.hpp"
#include "regex"
#include "Mesh.hpp"

namespace cookie {

	std::vector<Texture> AssetImporter::loadTexture(
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
			Texture target;
			textureProcessor->fillTexture(materialPath, target);
			target.type = assignType;
			textures.push_back(std::move(target));
		}
		return textures;
	}

	void AssetImporter::decodeMesh(
			const aiMesh *mesh,
			MeshData &target
	) {
		target.vertices = loadVertices(mesh);
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			auto &face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				target.indices.push_back(face.mIndices[j]);
		}
	}

	std::vector<Vertex> AssetImporter::loadVertices(const aiMesh *mesh) {
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

	//TODO add more textures support
	std::vector<Texture> AssetImporter::loadTextures(
			aiMaterial *material,
			const std::string &meshPath
	) {
		std::vector<Texture> textures;
		auto diffuseMaps = loadTexture(
				material,
				aiTextureType_DIFFUSE,
				Texture::Type::DIFFUSE,
				meshPath
		);
		std::move(diffuseMaps.begin(), diffuseMaps.end(), std::back_inserter(textures));
		auto specularMaps = loadTexture(
				material,
				aiTextureType_SPECULAR,
				Texture::Type::SPECULAR,
				meshPath
		);
		std::move(specularMaps.begin(), specularMaps.end(), std::back_inserter(textures));
		return textures;
	}


	void AssetImporter::importMesh(SceneObject& root, const std::string &path) {
		Assimp::Importer importer;
		const aiScene *scene = importer.ReadFile(
				path.c_str(),
				aiProcess_CalcTangentSpace |
				aiProcess_Triangulate |
				aiProcess_FlipUVs |
				aiProcess_JoinIdenticalVertices
		);
		// If the import failed, report it
		if (!scene || !scene->HasMeshes()) {
			throw std::runtime_error("Can't import asset at " + path);
		}
		const auto& materials = loadMaterials(scene, path);
		for (auto i = 0; i < scene->mNumMeshes; i++) {
			aiMesh *mesh = scene->mMeshes[i];
			auto meshData = std::make_unique<MeshData>();
			decodeMesh(mesh, *meshData);
			auto node = std::make_unique<SceneObject>();
			auto meshComponent = std::make_unique<Mesh>(std::move(meshData));
			node->addComponent(std::move(meshComponent));
			root.addChild(std::move(node));
		}
	}

	std::vector<Material> AssetImporter::loadMaterials(const aiScene *scene, const std::string &meshPath) {
		std::vector<Material> materials;
		materials.reserve(scene->mNumMaterials);
		for (auto i = 0; i < scene->mNumMaterials; i++) {
			aiMaterial *material = scene->mMaterials[i];
			Material target;
			aiColor3D color;

			material->Get(AI_MATKEY_NAME, target.name);
			material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
			target.diffuseColor = glm::vec3(color.r, color.g, color.b);
			material->Get(AI_MATKEY_COLOR_SPECULAR, color);
			target.specularColor = glm::vec3(color.r, color.g, color.b);
			material->Get(AI_MATKEY_COLOR_AMBIENT, color);
			target.ambientColor = glm::vec3(color.r, color.g, color.b);
			material->Get(AI_MATKEY_COLOR_EMISSIVE, color);
			target.emissiveColor = glm::vec3(color.r, color.g, color.b);
			material->Get(AI_MATKEY_COLOR_TRANSPARENT, color);
			target.transparencyColor = glm::vec3(color.r, color.g, color.b);
			material->Get(AI_MATKEY_OPACITY, target.opacity);
			material->Get(AI_MATKEY_SHININESS, target.shininess);
			material->Get(AI_MATKEY_REFRACTI, target.refraction);

			target.textures = loadTextures(material,meshPath.substr(0, meshPath.find_last_of('/')));

			materials.push_back(std::move(target));
		}
		return materials;
	}
}
