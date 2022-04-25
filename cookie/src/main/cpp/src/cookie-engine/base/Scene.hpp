//
//  Scene.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 06.07.2021.
//
#ifndef Scene_hpp
#define Scene_hpp

#include <glm/glm.hpp>
#include <memory>
#include "DrawUtils.h"
#include "FramerateInfo.hpp"
#include "SceneSettings.hpp"
#include "CrossBatchBufferStorage.hpp"
#include "BatchManager.hpp"

namespace cookie {
	class Scene {
	private:
		std::unique_ptr<SceneSettings> sceneSettings;
		std::unique_ptr<CrossBatchBufferStorage> globalBufferStorage;
		std::unique_ptr<DrawUtils> drawUtils;
		std::unique_ptr<BatchManager> batchManager;
		std::vector<std::shared_ptr<SceneObject>> sceneObjects;
		FramerateInfo framerate;
		glm::mat4 vMat;

		void display(const std::chrono::steady_clock::time_point& currentTime, const std::chrono::steady_clock::time_point& currentTimeDelta);

	public:
		Scene();
		~Scene();

		void addObject(const std::shared_ptr<SceneObject>& sceneObject);
		void removeObject(const std::shared_ptr<SceneObject>& sceneObject);
		void startLoop();
		SceneSettings &getSettings();
	};
}

#endif /* Scene_hpp */
