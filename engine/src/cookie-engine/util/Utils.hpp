//
// Created by Antiufieiev Michael on 24.10.2021.
//

#ifndef COOKIE_ENGINE_UTILS_HPP
#define COOKIE_ENGINE_UTILS_HPP

#include <string>

namespace cookie {

	class Utils {
	public:
		static inline bool endsWith(const std::string &a, const std::string &b) {
			if (b.size() > a.size()) { return false; }
			return std::equal(a.begin() + a.size() - b.size(), a.end(), b.begin());
		}
		//static glm::mat4 convertMatrix(const aiMatrix4x4 &aiMat);
	};
}

#endif //COOKIE_ENGINE_UTILS_HPP
