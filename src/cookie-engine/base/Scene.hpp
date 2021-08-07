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
#include "ShaderManager.hpp"
#include "FramerateInfo.hpp"
#include "SceneSettings.hpp"
#include "Cube.hpp"
#include "Cookie.hpp"

namespace cookie {
    class Scene {
    private:
        std::unique_ptr<SceneSettings> sceneSettings;
        FramerateInfo framerate;
        glm::mat4 vMat;
        Cube cube;

        void display(double currentTime, double currentTimeDelta);

    public:

        Scene();
        ~Scene();

        void init();
        void startLoop();
    };
}

#endif /* Scene_hpp */
