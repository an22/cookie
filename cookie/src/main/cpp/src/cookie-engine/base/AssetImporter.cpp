//
// Created by Antiufieiev Michael on 18.08.2021.
//
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_NOEXCEPTION

#include "AssetImporter.hpp"
#include "CookieFactory.hpp"
#include "MeshStruct.h"
#include "SceneObject.hpp"

using namespace tinygltf;

static void parseScene(cookie::SceneObject &root, const Model &model) {

}

namespace cookie {

	void AssetImporter::importMesh(SceneObject &root, const std::string &path) {
		std::unique_ptr<tinygltf::Model> scene(readFbxFromFile(path));
		parseScene(root, *scene);
	}

	tinygltf::Model *AssetImporter::readFbxFromFile(const std::string &path) {
		size_t size;
		std::byte *bytes = CookieFactory::getManager().readEntireFile(path, size, false);
		auto *model = new tinygltf::Model();
		tinygltf::TinyGLTF loader;
		std::string err;
		std::string warn;
		bool ret = loader.LoadBinaryFromMemory(
				model,
				&err, &warn,
				reinterpret_cast<unsigned char *>(bytes),
				size
		);
		delete[] bytes;

		if (!warn.empty()) {
			printf("Warn: %s\n", warn.c_str());
		}

		if (!err.empty()) {
			printf("Err: %s\n", err.c_str());
		}

		return model;
	}
}
