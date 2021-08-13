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
#include <DrawUtils.h>
#include "FramerateInfo.hpp"
#include "SceneSettings.hpp"
#include "Cube.hpp"

namespace cookie {
	class Scene {
	private:
		std::unique_ptr<SceneSettings> sceneSettings;
		std::unique_ptr<DrawUtils> drawUtils;
		FramerateInfo framerate;
		glm::mat4 vMat;
		Cube cube;

		void display(double currentTime, double currentTimeDelta);

	public:
		Scene();
		~Scene();

		void startLoop();
		SceneSettings &getSettings();
	};
}

#endif /* Scene_hpp */
