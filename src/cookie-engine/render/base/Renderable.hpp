//
// Created by Michael on 6/13/2022.
//

#ifndef COOKIE_ENGINE_RENDERABLE_HPP
#define COOKIE_ENGINE_RENDERABLE_HPP

#include <memory>
#include <list>
#include "glm/fwd.hpp"


namespace cookie {
	class BufferStorage;

	class DrawUtils;

	class Material;

	struct MeshData;

	class Renderable {
	protected:
		std::unique_ptr<BufferStorage> bufferStorage;
		std::shared_ptr<Material> material;

	public:
		explicit Renderable(std::shared_ptr<Material> material);
		Renderable(Renderable &&other) = default;
		virtual ~Renderable();
		virtual void saveToGPU() = 0;
		virtual void render(const DrawUtils &drawUtils) = 0;
	};
}

#endif //COOKIE_ENGINE_RENDERABLE_HPP
