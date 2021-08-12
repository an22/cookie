//
// Created by Antiufieiev Michael on 07.08.2021.
//
#include <Mesh.hpp>
#include "Scene.hpp"

namespace cookie {
    Scene::Scene() : cube(0.0f, -2.0f, 0.0f) {
        auto width = cookie::engine->platformData->width();
        auto height = cookie::engine->platformData->height();
        drawUtils = CookieFactory::provideDrawUtils();
        sceneSettings = std::make_unique<SceneSettings>(
                width, height, 0.0f, 0.0f, 8.0f, 1.0472f, 0.1f, 1000.0f
        );
        vMat = glm::translate(glm::mat4(1.0f), -1.0f * sceneSettings->cameraPos);
    }

    Scene::~Scene() = default;

    void Scene::display(double currentTime, double currentTimeDelta) {
        drawUtils->clearBuffers();
        drawUtils->enableDepthTest();
        cube.draw(*drawUtils, vMat, sceneSettings->perspectiveMx);
        drawUtils->drawInstanced(0,36,10000);
    }

    void Scene::startLoop() {
        framerate.invalidateFrameRate();
        while (!drawUtils->shouldCloseWindow()) {
            display(framerate.frameTime, framerate.frameTime - framerate.framerateTimestamp);
            framerate.invalidateFrameRate();
            drawUtils->swapBuffers();
            drawUtils->listenInputEvents();
        }
    }
}
