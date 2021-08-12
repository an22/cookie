//
//  BufferStorage.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 01.07.2021.
//

#ifndef BufferStorage_hpp
#define BufferStorage_hpp

#include <cstdio>
#include <memory>
#include "PlatformSpecificBufferData.h"

namespace cookie {
    class BufferStorage {
    protected:
        size_t bufferSize;

    public:
        explicit BufferStorage(size_t bufferSize);
        virtual ~BufferStorage();

        virtual void bind() = 0;
        virtual void saveToBuffer(
                size_t size,
                const void *memory,
                std::unique_ptr<PlatformSpecificBufferData> data
        ) = 0;
    };
}

#endif /* BufferStorage_hpp */
