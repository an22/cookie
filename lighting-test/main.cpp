//
//  main.cpp
//  lighting-test
//
//  Created by Antiufieiev Michael on 21.06.2021.
//
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];

const char* loadShaderFrom(std::string path);

GLuint createShaderProgram() {
	auto vertex = loadShaderFrom("/Users/antiufieievmichael/Guides/lighting-test/lighting-test/vertex.glsl");
	auto fragment = loadShaderFrom("/Users/antiufieievmichael/Guides/lighting-test/lighting-test/fragment.glsl");
	
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	glShaderSource(vShader, 1, &vertex, NULL);
	glShaderSource(fShader, 1, &fragment, NULL);
	
	glCompileShader(vShader);
	glCompileShader(fShader);
	
	GLuint vfProgram = glCreateProgram();
	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);
	glLinkProgram(vfProgram);
	return vfProgram;
}

const char* loadShaderFrom(std::string path) {
	std::ifstream filestream(path, std::ios::in);
	if(!filestream.is_open()){
		throw "Cant read " + path;
	}
	
	std::stringstream buffer;
	buffer << filestream.rdbuf();
	std::string result = buffer.str();
	char* c_str = new char[result.size()];
	strcpy(c_str, result.c_str());
	return c_str;
}

void init(GLFWwindow & window){
	renderingProgram = createShaderProgram();
	glGenVertexArrays(numVAOs,vao);
	glBindVertexArray(vao[0]);
}

void display(GLFWwindow& window, double currentTime) {
	glUseProgram(renderingProgram);
	glPointSize(30.0f);
	glDrawArrays(GL_POINTS, 0, 1);
}

void error_callback(int code, const char* description)
{
	std::cout << description << std::endl;
}

int main(int argc, const char * argv[]) {
	if(!glfwInit()) exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwSetErrorCallback(error_callback);
	GLFWwindow* window = glfwCreateWindow(600, 600, "LightingTest", NULL, NULL);
	glfwMakeContextCurrent(window);
	if(glewInit() != GLEW_OK) exit(EXIT_FAILURE);
	glfwSwapInterval(1);
	
	init(*window);
	while (!glfwWindowShouldClose(window)) {
		display(*window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
