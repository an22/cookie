//
// Created by Michael on 4/16/2022.
//

#ifndef COOKIE_ANDROIDFILEMANAGER_HPP
#define COOKIE_ANDROIDFILEMANAGER_HPP

#include "FileManager.hpp"
#include <android/asset_manager.h>

namespace cookie {
	class AndroidFileManager : public cookie::FileManager {
	private:
		AAssetManager *manager;
	public:
		AndroidFileManager(AAssetManager *mgr);
		AAssetManager *getManager() const;
		std::byte *readEntireFile(
				const std::string &path,
				size_t &size,
				bool isStringExpected
		) const override;
	};
}

#endif //COOKIE_ANDROIDFILEMANAGER_HPP
