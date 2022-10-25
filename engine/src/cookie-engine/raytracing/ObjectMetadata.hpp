//
// Created by Michael on 7/27/2022.
//

#ifndef COOKIE_ENGINE_OBJECTMETADATA_HPP
#define COOKIE_ENGINE_OBJECTMETADATA_HPP

#include <vector>
#include "cstdint"

struct ObjectMetadata {
	uint32_t materialIndex;
	uint32_t primitiveType;
	uint32_t primitiveIndex;
	uint32_t boundingBox;
	std::vector<uint32_t> affectedLights;
};

#endif //COOKIE_ENGINE_OBJECTMETADATA_HPP
