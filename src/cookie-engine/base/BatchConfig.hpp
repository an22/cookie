//
// Created by Antiufieiev Michael on 23.10.2021.
//

#ifndef COOKIE_ENGINE_BATCHCONFIG_HPP
#define COOKIE_ENGINE_BATCHCONFIG_HPP


struct BatchConfig {
	unsigned int meshCount = 0;
	unsigned int* startOffset = nullptr;
	unsigned int* indicesSize = nullptr;
	unsigned int* baseVertexOffset = nullptr;

	~BatchConfig() {
		delete[] startOffset;
		delete[] indicesSize;
		delete[] baseVertexOffset;
	}
};


#endif //COOKIE_ENGINE_BATCHCONFIG_HPP
