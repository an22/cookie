//
// Created by Michael on 4/16/2022.
//
#ifdef __ANDROID__

#include "AndroidFileManager.hpp"
#include <android/asset_manager.h>

namespace cookie {
	std::byte *AndroidFileManager::readEntireFile(
			const std::string &path, size_t &size,
			bool isStringExpected
	) const {
		auto *asset = AAssetManager_open(manager, path.c_str(), AASSET_MODE_UNKNOWN);
		int64_t fileLength = AAsset_getRemainingLength(asset);
		auto *fileContent = new std::byte[sizeof(std::byte) * (fileLength + isStringExpected)];
		if (isStringExpected) {
			fileContent[fileLength] = static_cast<std::byte>(0);
		}
		AAsset_read(asset, fileContent, fileLength);
		AAsset_close(asset);
		size = fileLength + isStringExpected;
		return fileContent;
	}

	AndroidFileManager::AndroidFileManager(AAssetManager *mgr) : manager(mgr) {
	}

	AAssetManager *AndroidFileManager::getManager() const {
		return manager;
	}
}

#endif
