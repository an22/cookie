//
// Created by Antiufieiev Michael on 23.10.2021.
//

#ifndef COOKIE_ENGINE_BATCHCONFIG_HPP
#define COOKIE_ENGINE_BATCHCONFIG_HPP

#include <vector>

namespace cookie {
	struct BatchConfig {
		unsigned int meshCount = 0;
		std::vector<int32_t> startOffset;
		std::vector<int32_t> indicesSize;
		std::vector<int32_t> baseVertexOffset;
	};
}


#endif //COOKIE_ENGINE_BATCHCONFIG_HPP
