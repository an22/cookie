//
// Created by Michael on 4/16/2022.
//

#ifndef COOKIE_FILEMANAGER_HPP
#define COOKIE_FILEMANAGER_HPP

#include <string>

namespace cookie {
	class FileManager {
	public:
		virtual std::byte* readEntireFile(const std::string &path,size_t &size, bool isStringExpected) const = 0;
		[[nodiscard]] virtual std::string readStringFromFile(const std::string &path, bool isStringExpected) const = 0;
		virtual ~FileManager() = default;
	};
}

#endif //COOKIE_FILEMANAGER_HPP
