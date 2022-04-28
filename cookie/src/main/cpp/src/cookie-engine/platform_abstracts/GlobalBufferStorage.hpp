//
// Created by Antiufieiev Michael on 21.10.2021.
//

#ifndef COOKIE_ENGINE_CROSSBATCHBUFFERSTORAGE_HPP
#define COOKIE_ENGINE_CROSSBATCHBUFFERSTORAGE_HPP

#include "glm/glm.hpp"
#include "MeshStruct.h"

namespace cookie {
	class GlobalBufferStorage {
	public:
		explicit GlobalBufferStorage() = default;
		virtual ~GlobalBufferStorage() = default;
		virtual void bind() = 0;
		virtual void createFaceBuffer() = 0;
		virtual void createLightBuffer() = 0;
		virtual void createFaceIndexHashesBuffer() = 0;
		virtual void createFaceIndexesBuffer() = 0;
		virtual void createMaterialsBuffer() = 0;
		virtual void updateMatrices(const glm::mat4& projection, const glm::mat4& view) = 0;
	};
}

#endif //COOKIE_ENGINE_CROSSBATCHBUFFERSTORAGE_HPP
