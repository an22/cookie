//
//  main.cpp
//  lighting-test
//
//  Created by Antiufieiev Michael on 21.06.2021.
//
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Scene.hpp"
#include <iostream>

void errorCallback(int code, const char* description)
{
	std::cout << description << std::endl;
}

GLFWwindow* initOpenGL() {
	if(!glfwInit()) exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwSetErrorCallback(errorCallback);
	GLFWwindow* window = glfwCreateWindow(600, 600, "LightingTest", NULL, NULL);
	glfwMakeContextCurrent(window);
	if(glewInit() != GLEW_OK) exit(EXIT_FAILURE);
	glfwSwapInterval(1);
	return window;
}

int main(int argc, const char * argv[]) {
	GLFWwindow* window = initOpenGL();
	Scene scene;
	scene.init(window);
	scene.startLoop();
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
