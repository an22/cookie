//
// Created by Antiufieiev Michael on 08.08.2021.
//

#include "GLErrorHandler.hpp"
#include <GLFW/glfw3.h>
#include "OpenGLDrawUtils.h"
#include "Cookie.hpp"
#include "OpenGLPlatformSpecificData.h"

bool OpenGLDrawUtils::shouldCloseWindow() const {
	auto &platformData = dynamic_cast<OpenGLPlatformSpecificData &>(*cookie::Cookie::getInstance().platformData);
	return glfwWindowShouldClose(platformData.getWindow());
}

void OpenGLDrawUtils::clearBuffers() const {
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void OpenGLDrawUtils::listenInputEvents() const {
	auto &platformData = dynamic_cast<OpenGLPlatformSpecificData &>(*cookie::Cookie::getInstance().platformData);
	glfwSwapBuffers(platformData.getWindow());
}

void OpenGLDrawUtils::swapBuffers() const {
	glfwPollEvents();
}

void OpenGLDrawUtils::enableDepthTest() const {
}

void OpenGLDrawUtils::drawInstanced(int32_t first, int32_t size, int32_t times) const {
	glDrawArraysInstanced(GL_TRIANGLES, first, size, times);
}

void OpenGLDrawUtils::drawArrays(int32_t from, int32_t to) const {
	glDrawArrays(GL_TRIANGLES, from, to);
}

void OpenGLDrawUtils::drawElements(int32_t size) const {
	glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, nullptr);
}

void OpenGLDrawUtils::cullFace() const {
}

void OpenGLDrawUtils::drawMultiElementsWithIndexOffset(
		unsigned int meshCount,
		const int32_t *startOffset,
		const int32_t *indicesCount,
		const int32_t *vertexOffset
) const {
	GLErrorHandler handler;
	std::vector<void *> pointers(meshCount);
	for (int i = 0; i < meshCount; i++) {
		pointers[i] = reinterpret_cast<void *>(startOffset[i]);
	}
	glMultiDrawElementsBaseVertex(
			GL_TRIANGLES,
			indicesCount,
			GL_UNSIGNED_INT,
			pointers.data(),
			static_cast<int>(meshCount),
			vertexOffset
	);
	handler.checkOpenGLError();
}
