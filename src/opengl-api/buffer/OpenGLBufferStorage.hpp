//
//  OpenGLBufferStorage.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#ifndef OpenGLBufferStorage_hpp
#define OpenGLBufferStorage_hpp

#include <stdio.h>
#include "BufferStorage.hpp"
#include "PlatformSpecificData.hpp"

class OpenGLBufferStorage : public cookie::BufferStorage {
public:
	OpenGLBufferStorage(size_t bufferSize):cookie::BufferStorage(bufferSize) {}
	void saveToBuffer(
					  size_t size,
					  const void* memory,
					  int32_t usage,
					  cookie::PlatformSpecificData* data
					  ) const override;
	~OpenGLBufferStorage() override = default;
};

#endif /* OpenGLBufferStorage_hpp */
