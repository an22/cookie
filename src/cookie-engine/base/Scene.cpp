//
// Created by Antiufieiev Michael on 07.08.2021.
//
#include "Scene.hpp"

namespace cookie {
    Scene::Scene() : cube(0.0f, -2.0f, 0.0f) {
        auto width = cookie::engine->platformData->width();
        auto height = cookie::engine->platformData->height();
        sceneSettings = std::make_unique<SceneSettings>(
                width, height, 0.0f, 0.0f, 8.0f, 1.0472f, 0.1f, 1000.0f
        );
        vMat = glm::translate(glm::mat4(1.0f), -1.0f * sceneSettings->cameraPos);
    }

    Scene::~Scene() = default;

    void Scene::init() {
        //		glGenVertexArrays(static_cast<int>(bufferStorage.arrayObjectsSize), bufferStorage.vao);
        //		glBindVertexArray(bufferStorage.vao[0]);
        //		glGenBuffers(static_cast<int>(bufferStorage.bufferObjectsSize), bufferStorage.vbo);
        //		glBindBuffer(GL_ARRAY_BUFFER, bufferStorage.vbo[0]);
        //		float* mesh = Cube::genMesh();
        //		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Cube::meshSize, mesh, GL_STATIC_DRAW);
        //		delete [] mesh;
    }

    void Scene::display(double currentTime, double currentTimeDelta) {
        //		glClear(GL_DEPTH_BUFFER_BIT);
        //		glClear(GL_COLOR_BUFFER_BIT);
        //		glUseProgram(renderingProgram);
        //		projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
        //		vLoc = glGetUniformLocation(renderingProgram, "v_matrix");
        //		tFactLoc = glGetUniformLocation(renderingProgram, "timeFactor");
        //
        //		glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(vMat));
        //		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(sceneSettings->perspectiveMx));
        //		glUniform1f(tFactLoc, (float) currentTime);
        //
        //		glBindBuffer(GL_ARRAY_BUFFER, bufferStorage.vbo[0]);
        //		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        //		glEnableVertexAttribArray(0);
        //
        //		glEnable(GL_DEPTH_TEST);
        //		glDepthFunc(GL_LEQUAL);
        //		glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 100000);
    }

    void Scene::startLoop() {
        framerate.invalidateFrameRate();
        while (true) {
            display(framerate.frameTime, framerate.frameTime - framerate.framerateTimestamp);
            framerate.invalidateFrameRate();
        }
    }
}
