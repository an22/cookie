//
//  Scene.hpp
//  lighting-test
//
//  Created by Antiufieiev Michael on 06.07.2021.
//
#ifndef Scene_hpp
#define Scene_hpp
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ShaderManager.hpp"
#include "FramerateInfo.hpp"
#include "BufferStorage.hpp"
#include "SceneSettings.hpp"
#include "Cube.hpp"
#endif /* Scene_hpp */

class Scene {
private:
	SceneSettings* sceneSettings;
	FramerateInfo framerate;
	BufferStorage bufferStorage;
	GLuint renderingProgram, mvLoc, projLoc;
	glm::mat4 vMat, mvMat;
	Cube cube;
	
	GLFWwindow* windRef;
	
	void display(const GLFWwindow& window, double currentTime, double currentTimeDelta) {
		glClear(GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(renderingProgram);
		mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
		projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
		
		vMat = glm::translate(glm::mat4(1.0f), -1.0f * sceneSettings->cameraPos);
		mvMat = vMat * cube.getModelMat();
		
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(sceneSettings->perspectiveMx));
		
		glBindBuffer(GL_ARRAY_BUFFER, bufferStorage.vbo[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
public:
	
	Scene() :bufferStorage(1,2),cube(0.0f,-2.0f,0.0f) {}
	
	~Scene() {
		delete sceneSettings;
	}
	
	void init(GLFWwindow* window){
		windRef = window;
		renderingProgram = ShaderManager::createShaderProgram();
		sceneSettings = new SceneSettings(0.0f, 0.0f, 8.0f, window, 1.0472f, 0.1f, 1000.0f);
		glGenVertexArrays(static_cast<int>(bufferStorage.arrayObjectsSize), bufferStorage.vao);
		glBindVertexArray(bufferStorage.vao[0]);
		glGenBuffers(static_cast<int>(bufferStorage.bufferObjectsSize), bufferStorage.vbo);
		glBindBuffer(GL_ARRAY_BUFFER, bufferStorage.vbo[0]);
		float* mesh = Cube::genMesh();
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Cube::meshSize, mesh, GL_STATIC_DRAW);
		delete [] mesh;
	}
	
	void startLoop() {
		framerate.invalidateFrameRate();
		if(windRef == nullptr) throw "Window can't be null";
		while (!glfwWindowShouldClose(windRef)) {
			display(*windRef, glfwGetTime(), glfwGetTime() - framerate.framerateTimestamp);
			framerate.invalidateFrameRate();
			glfwSwapBuffers(windRef);
			glfwPollEvents();
		}
	}
	
};
