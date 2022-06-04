//
// Created by Antiufieiev Michael on 10.10.2021.
//

#ifndef COOKIE_ENGINE_BATCHMANAGER_HPP
#define COOKIE_ENGINE_BATCHMANAGER_HPP

#include <unordered_map>
#include "cookie-engine/component/Material.h"
#include "Batch.hpp"
#include "DrawUtils.h"

namespace cookie {

	typedef std::unordered_map<std::shared_ptr<Material>, std::unique_ptr<Batch>> MaterialBatchMap;

	class BatchManager {
	private:
		MaterialBatchMap batchMap;
	public:

		BatchManager();

		void onNewObject(const std::shared_ptr<SceneObject>& sceneObject);
		void draw(const DrawUtils& drawUtils) const;
		void syncWithVideoBuffer();
	};
}

#endif //COOKIE_ENGINE_BATCHMANAGER_HPP
