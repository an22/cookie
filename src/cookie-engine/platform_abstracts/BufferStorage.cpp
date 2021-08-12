//
// Created by Antiufieiev Michael on 07.08.2021.
//
#include "BufferStorage.hpp"

namespace cookie {
    BufferStorage::BufferStorage(size_t bufferSize) {
        this->bufferSize = bufferSize;
    }

    BufferStorage::~BufferStorage() = default;
}

