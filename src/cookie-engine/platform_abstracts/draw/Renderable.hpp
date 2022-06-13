//
// Created by Michael on 6/13/2022.
//

#ifndef COOKIE_ENGINE_RENDERABLE_HPP
#define COOKIE_ENGINE_RENDERABLE_HPP

#include <memory>
#include <vector>
#include "glm/fwd.hpp"


namespace cookie {
	class BufferStorage;

	class DrawUtils;

	struct MeshData;

	class Renderable {
	protected:
		std::unique_ptr<BufferStorage> bufferStorage;
		virtual void draw(const DrawUtils &drawUtils) = 0;
		virtual void saveToGPUInternal(const MeshData &meshData, const std::vector<glm::mat4> &matrices);
	public:
		explicit Renderable();
		virtual ~Renderable();
		virtual	void saveToGPU() = 0;
		virtual void render(const DrawUtils &drawUtils);
	};
}

#endif //COOKIE_ENGINE_RENDERABLE_HPP
