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
#include "SceneSectorManager.hpp"
#include "SceneSettings.hpp"
#include "GlobalBufferStorage.hpp"
#include "BatchManager.hpp"

namespace cookie {
	class Scene {
	private:
		std::unique_ptr<SceneSectorManager> sceneSectorManager;
		std::unique_ptr<SceneSettings> sceneSettings;
		std::unique_ptr<GlobalBufferStorage> globalBufferStorage;
		std::unique_ptr<DrawUtils> drawUtils;
		std::unique_ptr<BatchManager> batchManager;
		std::vector<std::shared_ptr<SceneObject>> sceneObjects;
		FramerateInfo framerate;
		glm::mat4 vMat;

	protected:
		virtual void display(const std::chrono::steady_clock::time_point &currentTime,
							 const std::chrono::steady_clock::time_point &currentTimeDelta);

	public:
		Scene();
		virtual ~Scene();
		virtual void addObject(const std::shared_ptr<SceneObject> &sceneObject);
		virtual void removeObject(const std::shared_ptr<SceneObject> &sceneObject);
		virtual void prepareRendering();
		virtual void renderFrame();
		SceneSettings &getSettings();
	};
}

#endif /* Scene_hpp */
