//
// Created by Antiufieiev Michael on 21.10.2021.
//

#ifndef COOKIE_ENGINE_CROSSBATCHBUFFERSTORAGE_HPP
#define COOKIE_ENGINE_CROSSBATCHBUFFERSTORAGE_HPP

#include "glm/glm.hpp"

namespace cookie {
	class CrossBatchBufferStorage {
	public:
		explicit CrossBatchBufferStorage() = default;
		virtual ~CrossBatchBufferStorage() = default;
		virtual void bind() = 0;
		virtual void updateMatrices(const glm::mat4& projection, const glm::mat4& view) = 0;
	};
}

#endif //COOKIE_ENGINE_CROSSBATCHBUFFERSTORAGE_HPP
