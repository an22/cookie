//
//  BufferStorage.hpp
//  lighting-test
//
//  Created by Antiufieiev Michael on 01.07.2021.
//

#ifndef BufferStorage_hpp
#define BufferStorage_hpp

#include "PlatformSpecificData.hpp"

namespace cookie {
class BufferStorage {
protected:
	size_t bufferSize;
	
public:
	BufferStorage(size_t bufferSize) {
		this->bufferSize = bufferSize;
	}
	
	virtual ~BufferStorage() {
	}
	
	
	virtual void saveToBuffer(
							  size_t size,
							  const void* memory,
							  int32_t usage,
							  PlatformSpecificData* data
							  ) const = 0;
};
}

#endif /* BufferStorage_hpp */
