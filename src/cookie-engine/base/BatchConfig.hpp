//
// Created by Antiufieiev Michael on 23.10.2021.
//

#ifndef COOKIE_ENGINE_BATCHCONFIG_HPP
#define COOKIE_ENGINE_BATCHCONFIG_HPP


struct BatchConfig {
	unsigned int meshCount = 0;
	int32_t* indicesSize = nullptr;
	int32_t* baseVertexOffset = nullptr;

	~BatchConfig() {
		delete[] indicesSize;
		delete[] baseVertexOffset;
	}
};


#endif //COOKIE_ENGINE_BATCHCONFIG_HPP
