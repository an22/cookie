//
// Created by Antiufieiev Michael on 18.08.2021.
//

#ifndef COOKIE_ENGINE_ASSETIMPORTER_HPP
#define COOKIE_ENGINE_ASSETIMPORTER_HPP

#include "MeshStruct.h"
#include "SceneObject.hpp"
#include <string>
#include <vector>
#include <tiny_gltf.h>

namespace cookie {
	class AssetImporter {
	private:
		static inline tinygltf::Model *readFbxFromFile(const std::string &path);
	public:
		static void importMesh(SceneObject &root, const std::string &path);
	};
}

#endif //COOKIE_ENGINE_ASSETIMPORTER_HPP
