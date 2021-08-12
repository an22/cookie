//
//  OpenGLBufferStorage.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#ifndef OpenGLBufferStorage_hpp
#define OpenGLBufferStorage_hpp

#include <GL/glew.h>
#include "BufferStorage.hpp"
#include "PlatformSpecificBufferData.h"
#include "OpenGLPSBufferData.h"

class OpenGLBufferStorage : public cookie::BufferStorage {
private:
    GLuint vao{};
    GLuint vboVertex{};
    GLuint vboIndex{};

    std::unique_ptr<OpenGLPSBufferData> bufferData;

public:
    explicit OpenGLBufferStorage();


    void bind() override;
    void saveToBuffer(
            const cookie::MeshData &meshData,
            std::unique_ptr<cookie::PlatformSpecificBufferData> data
    ) override;

    ~OpenGLBufferStorage() override;
};

#endif /* OpenGLBufferStorage_hpp */
