//
// Created by Antiufieiev Michael on 10.10.2021.
//

#ifndef COOKIE_ENGINE_BATCH_HPP
#define COOKIE_ENGINE_BATCH_HPP

#include <memory>
#include <list>
#include "MultiDrawConfig.h"
#include "Renderable.hpp"

namespace cookie {

	struct Vertex;
	class SceneObject;
	class Material;
	class DrawUtils;
	class BufferStorage;

	class Batch : Renderable {
	private:
		std::list<std::shared_ptr<SceneObject>> sceneObjects;
		MultiDrawConfig config;

		bool isStatic = true;
	public:

		explicit Batch(const std::shared_ptr<Material> &material);
		Batch(Batch&& other) noexcept;
		~Batch() override;

		void addObject(std::shared_ptr<SceneObject> sceneObject);
		void removeObject(const std::shared_ptr<SceneObject> &sceneObject);
		void saveToGPU() override;
		void render(const cookie::DrawUtils &drawUtils) override;
	};
}


#endif //COOKIE_ENGINE_BATCH_HPP
