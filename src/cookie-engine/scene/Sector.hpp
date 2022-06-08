//
// Created by Michael on 4/25/2022.
//

#ifndef COOKIE_SECTOR_HPP
#define COOKIE_SECTOR_HPP

#include <unordered_set>
#include <cstdint>

namespace cookie {
	struct Sector {
		std::unordered_set<uint32_t> indexList;
	};
}

#endif //COOKIE_SECTOR_HPP
