//
//  OpenGLBufferStorage.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include "OpenGLBufferStorage.hpp"

void OpenGLBufferStorage::saveToBuffer(
        size_t size,
        const void *memory,
        int32_t usage,
        cookie::PlatformSpecificData *data
) const {

}

OpenGLBufferStorage::OpenGLBufferStorage(size_t bufferSize) : cookie::BufferStorage(bufferSize) {}
