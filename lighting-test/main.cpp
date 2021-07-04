//
//  main.cpp
//  lighting-test
//
//  Created by Antiufieiev Michael on 21.06.2021.
//
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "ShaderManager.hpp"
#include "FramerateInfo.hpp"
#include "BufferStorage.hpp"

FramerateInfo framerate;
BufferStorage bufferStorage(1,2);
GLuint renderingProgram;

float x = 0.0f;
float inc = 0.0f;

GLuint loadShaderFrom(std::string path, GLenum shaderType);

void errorCallback(int code, const char* description)
{
	std::cout << description << std::endl;
}

void init(GLFWwindow & window){
	renderingProgram = ShaderManager::createShaderProgram();
	glGenVertexArrays(static_cast<int>(bufferStorage.arrayObjectsSize), bufferStorage.vao);
	glBindVertexArray(bufferStorage.vao[0]);
}

void display(GLFWwindow& window, double currentTime) {
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(renderingProgram);
	GLuint offsetLoc = glGetUniformLocation(renderingProgram, "offset");
	glProgramUniform1f(renderingProgram, offsetLoc, 1);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main(int argc, const char * argv[]) {
	if(!glfwInit()) exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwSetErrorCallback(errorCallback);
	GLFWwindow* window = glfwCreateWindow(600, 600, "LightingTest", NULL, NULL);
	glfwMakeContextCurrent(window);
	if(glewInit() != GLEW_OK) exit(EXIT_FAILURE);
	init(*window);
	while (!glfwWindowShouldClose(window)) {
		framerate.invalidateFrameRate();
		display(*window, framerate.framerateTimestamp);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
