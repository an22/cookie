//
// Created by Michael on 6/15/2022.
//

#ifndef COOKIE_ENGINE_MULTIDRAWCONFIG_H
#define COOKIE_ENGINE_MULTIDRAWCONFIG_H

#include <cstdint>
#include <vector>

namespace cookie {
	struct MultiDrawConfig {
		uint32_t meshCount = 0;
		std::vector<int32_t> startOffset;
		std::vector<int32_t> indicesSize;
		std::vector<int32_t> baseVertexOffset;
	};
}

#endif //COOKIE_ENGINE_MULTIDRAWCONFIG_H
