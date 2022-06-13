//
// Created by Antiufieiev Michael on 08.08.2021.
//
#include "config.hpp"

#if COOKIE_OPENGL

#include <GL/glew.h>
#include "OpenGLDrawUtils.h"
#include "Cookie.hpp"
#include "OpenGLPlatformSpecificData.h"
#include "GLErrorHandler.hpp"
#include "Bounds.hpp"

namespace cookie {
	bool OpenGLDrawUtils::shouldCloseWindow() const {
		return glfwWindowShouldClose(
				cookie::Cookie::getInstance()
						.getPlatformData<OpenGLPlatformSpecificData>()
						.getWindow()
		);
	}

	void OpenGLDrawUtils::clearBuffers() const {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}

	void OpenGLDrawUtils::swapBuffers() const {
		glfwSwapBuffers(
				cookie::Cookie::getInstance()
						.getPlatformData<OpenGLPlatformSpecificData>()
						.getWindow()
		);
		glfwPollEvents();
		GLErrorHandler::checkOpenGLError();
	}

	void OpenGLDrawUtils::enableDepthTest() const {
		glEnable(GL_DEPTH_TEST);
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
		glEnable(GL_CULL_FACE);
	}

	void OpenGLDrawUtils::setViewport(int32_t width, int32_t height) const {
		glViewport(0, 0, width, height);
	}

	void OpenGLDrawUtils::drawMultiElementsWithIndexOffset(
			uint32_t meshCount,
			int32_t *startOffset,
			int32_t *indicesCount,
			int32_t *vertexOffset
	) const {
		std::vector<void *> pointers(meshCount);
		for (int i = 0; i < meshCount; i++) {
			pointers[i] = reinterpret_cast<void *>(startOffset[i]);
		}
		glMultiDrawElementsBaseVertex(
				GL_TRIANGLES,
				reinterpret_cast<GLsizei *>(indicesCount),
				GL_UNSIGNED_INT,
				pointers.data(),
				static_cast<GLsizei>(meshCount),
				reinterpret_cast<GLint *>(vertexOffset)
		);
		GLErrorHandler::checkOpenGLError();
	}

	void OpenGLDrawUtils::drawBounds(const Bounds &bounds) const {
		GLErrorHandler::checkOpenGLError();
		glUseProgram(0);
		glMatrixMode(GL_PROJECTION);
		GLErrorHandler::checkOpenGLError();
		glLoadIdentity();
		GLErrorHandler::checkOpenGLError();
		glOrtho (-100.0f, 100.0f, -100.0f, 100.0f, -100.0f, 100.0f);
		GLErrorHandler::checkOpenGLError();
		glBegin(GL_POINTS);
		GLErrorHandler::checkOpenGLError();
		for (auto &point: bounds.points) {
			auto a = glm::normalize(point);
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(a.x, a.y, a.z);
		}
		GLErrorHandler::checkOpenGLError();
		glEnd();
		glFlush();
		GLErrorHandler::checkOpenGLError();
	}

	OpenGLDrawUtils::OpenGLDrawUtils() = default;
}

#endif