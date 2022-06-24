//
// Created by Michael on 5/26/2022.
//

#include "DefaultFileManager.hpp"
#include <fstream>

namespace cookie {
	std::byte *DefaultFileManager::readEntireFile(const std::string &path, size_t &size, bool isStringExpected) const {
		std::ifstream t(path);
		t.seekg(0, std::ios::end);
		size = t.tellg();
		auto *buffer = new char[size + isStringExpected];
		t.seekg(0);
		t.read(buffer, static_cast<std::streamsize>(size));
		return reinterpret_cast<std::byte *>(buffer);
	}

	std::string DefaultFileManager::readStringFromFile(const std::string &path, bool isStringExpected) const {
		std::ifstream ifs(path);
		if (!ifs.is_open()) {
			throw std::runtime_error("File not found at " + path);
		}
		return std::string{
				std::istreambuf_iterator<char>(ifs),
				std::istreambuf_iterator<char>()
		};
	}
} // cookie