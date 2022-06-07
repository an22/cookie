//
// Created by Michael on 5/26/2022.
//

#ifndef COOKIE_ENGINE_DEFAULTFILEMANAGER_HPP
#define COOKIE_ENGINE_DEFAULTFILEMANAGER_HPP

#include "FileManager.hpp"

namespace cookie {

	class DefaultFileManager : public cookie::FileManager {
	public:
		std::byte *readEntireFile(
				const std::string &path,
				size_t &size,
				bool isStringExpected
		) const override;
		[[nodiscard]] std::string readStringFromFile(const std::string &path, bool isStringExpected) const override;
	};

} // cookie

#endif //COOKIE_ENGINE_DEFAULTFILEMANAGER_HPP
