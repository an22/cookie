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
#include "MeshStruct.h"
#include "PlatformSpecificBufferData.h"

namespace cookie {
    class BufferStorage {

    public:
        explicit BufferStorage();
        virtual ~BufferStorage();

        virtual void bind() = 0;
        virtual void saveToBuffer(
                const MeshData &meshData,
                std::unique_ptr<PlatformSpecificBufferData> data
        ) = 0;
    };
}

#endif /* BufferStorage_hpp */
