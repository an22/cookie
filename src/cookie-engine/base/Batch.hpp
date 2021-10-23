//
// Created by Antiufieiev Michael on 10.10.2021.
//

#ifndef COOKIE_ENGINE_BATCH_HPP
#define COOKIE_ENGINE_BATCH_HPP

#include "memory"
#include "Material.h"
#include "SceneObject.hpp"
#include "BufferStorage.hpp"
#include "BatchConfig.hpp"
#include "DrawUtils.h"

namespace cookie {

	class Batch {
	private:
		std::vector<std::shared_ptr<SceneObject>> sceneObjects;
		std::unique_ptr<BufferStorage> bufferStorage;
		std::shared_ptr<Material> material;
		BatchConfig config;

		bool isStatic = true;
	public:

		explicit Batch(const std::shared_ptr<Material> &material);

		void addObject(std::shared_ptr<SceneObject> sceneObject);
		void removeObject(const std::shared_ptr<SceneObject>& sceneObject);
		void syncWithVideoBuffer();
		void draw(const DrawUtils& drawUtils);
	};
}


#endif //COOKIE_ENGINE_BATCH_HPP
