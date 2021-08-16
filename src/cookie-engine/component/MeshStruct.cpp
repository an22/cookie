//
// Created by Antiufieiev Michael on 12.08.2021.
//

#include "MeshStruct.h"

namespace cookie {

	Texture::Texture(unsigned int id, char byteSize) : id(id),
													   byteSize(byteSize) {
	}

	MeshData::MeshData(
			std::vector<Vertex> vertices,
			std::vector<unsigned int> indices,
			std::vector<Texture> textures
	) : vertices(std::move(vertices)),
		indices(std::move(indices)),
		textures(std::move(textures)) {
	}

	MeshData::MeshData(const aiMesh *scene) :
			vertices{},
			indices{},
			textures{} {
		for (unsigned int i = 0; i < scene->mNumVertices; i++) {
			Vertex vertex{};
			auto aiVertex = scene->mVertices[i];
			vertex.position = glm::vec3(aiVertex.x, aiVertex.y, aiVertex.z);
			if(scene->mNormals) {
				auto aiNormal = scene->mNormals[i];
				vertex.normal = glm::vec3(aiNormal.x, aiNormal.y, aiNormal.z);
			}
			if (scene->mTextureCoords[0]) {
				auto texCoord = scene->mTextureCoords[0][i];
				vertex.texCoords = glm::vec2(texCoord.x, texCoord.y);
			} else {
				vertex.texCoords = glm::vec2(0.0f, 0.0f);
			}
			vertices.emplace_back(vertex);
		}
		for (unsigned int i = 0; i < scene->mNumFaces; i++) {
			aiFace face = scene->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
	}

	Vertex::Vertex(
			const glm::vec3 &position,
			const glm::vec3 &normal,
			const glm::vec2 &texCoords
	) : position(position),
		normal(normal),
		texCoords(texCoords) {
	}
}
