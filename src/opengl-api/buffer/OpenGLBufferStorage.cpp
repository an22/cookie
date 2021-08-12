//
//  OpenGLBufferStorage.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include "OpenGLBufferStorage.hpp"
#include "GL/glew.h"
#include "OpenGLPSBufferData.h"

void OpenGLBufferStorage::saveToBuffer(
        size_t size,
        const void *memory,
        const std::unique_ptr<cookie::PlatformSpecificBufferData> data
) {
    auto &_bufferData = dynamic_cast<const OpenGLPSBufferData&>(*data);
    bufferData = std::make_unique<OpenGLPSBufferData>(_bufferData);
    glBindVertexArray(vao);
    glBindBuffer(bufferData->target, vbo);
    glBufferData(bufferData->target, sizeof(float) * size, memory, bufferData->usage);
}

OpenGLBufferStorage::OpenGLBufferStorage(size_t bufferSize) : cookie::BufferStorage(bufferSize) {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(static_cast<GLsizei>(bufferSize), &vbo);
}

OpenGLBufferStorage::~OpenGLBufferStorage() {
    glDeleteBuffers(static_cast<GLsizei>(bufferSize), &vbo);
    glDeleteVertexArrays(1, &vao);
}

void OpenGLBufferStorage::bind() {
    glBindVertexArray(vao);
    glBindBuffer(bufferData->target, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}
