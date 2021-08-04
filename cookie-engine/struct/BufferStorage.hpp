//
//  BufferStorage.hpp
//  lighting-test
//
//  Created by Antiufieiev Michael on 01.07.2021.
//

#ifndef BufferStorage_hpp
#define BufferStorage_hpp

#include "PlatformSpecificData.hpp"

class BufferStorage {
	
	std::size_t bufferSize;
	
	BufferStorage(std::size_t bufferSize) {
		this->bufferSize = bufferSize;
	}
	
	virtual ~BufferStorage() {
	}
	
	
	virtual void saveToBuffer(
							  std::size_t size,
							  const void* memory,
							  int32_t usage,
							  PlatformSpecificData* data
							  ) const;
};

#endif /* BufferStorage_hpp */
