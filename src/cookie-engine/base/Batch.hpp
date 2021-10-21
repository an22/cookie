//
// Created by Antiufieiev Michael on 10.10.2021.
//

#ifndef COOKIE_ENGINE_BATCH_HPP
#define COOKIE_ENGINE_BATCH_HPP

#include "memory"
#include "Material.h"
#include "SceneObject.hpp"
#include "BufferStorage.hpp"

namespace cookie {

	class Batch {
	private:
		std::vector<std::shared_ptr<SceneObject>> sceneObjects;
		bool isStatic = true;

	public:

		void addObject(std::shared_ptr<SceneObject> sceneObject);
		void removeObject(std::shared_ptr<SceneObject> sceneObject);
		void syncWithVideoBuffer(const BufferStorage &bufferStorage);
	};
}


#endif //COOKIE_ENGINE_BATCH_HPP
