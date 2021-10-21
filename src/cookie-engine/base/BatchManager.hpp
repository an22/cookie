//
// Created by Antiufieiev Michael on 10.10.2021.
//

#ifndef COOKIE_ENGINE_BATCHMANAGER_HPP
#define COOKIE_ENGINE_BATCHMANAGER_HPP

#include "Material.h"
#include "Batch.hpp"
#include "BufferStorage.hpp"
#include <unordered_map>

namespace cookie {

	typedef std::unordered_map<std::shared_ptr<Material>, std::unique_ptr<Batch>> MaterialBatchMap;

	class BatchManager {
	private:
		MaterialBatchMap batchMap;
		std::unique_ptr<BufferStorage> bufferStorage;
	public:

		BatchManager();

		void onNewObject(const std::shared_ptr<SceneObject>& sceneObject);
		void syncWithVideoBuffer();
	};
}

#endif //COOKIE_ENGINE_BATCHMANAGER_HPP
