//
// Created by Antiufieiev Michael on 18.08.2021.
//

#include "AssetImporter.hpp"
#include "Mesh.hpp"
#include <CookieFactory.hpp>
#include "SceneObject.hpp"

static void parseScene(cookie::SceneObject &root, const ofbx::Object *rootScene) {

}

namespace cookie {

	void AssetImporter::importMesh(SceneObject &root, const std::string &path) {
		std::unique_ptr<ofbx::IScene, std::function<void(ofbx::IScene *)>> scene(
				readFbxFromFile(path),
				[](ofbx::IScene *s) { s->destroy(); }
		);
		scene->getRoot()
		parseScene(root, scene->getRoot());
	}

	ofbx::IScene *AssetImporter::readFbxFromFile(const std::string &path) {
		size_t size;
		std::byte *fbx = CookieFactory::getManager().readEntireFile(path, size, false);
		ofbx::IScene *scene = ofbx::load(reinterpret_cast<const ofbx::u8 *>(fbx),
										 static_cast<int>(size),
										 (ofbx::u64) ofbx::LoadFlags::TRIANGULATE);
		return scene;
	}
}
