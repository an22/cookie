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

namespace cookie {

	GLenum convertDrawMode(DrawMode drawMode) {
		GLenum mode;
		switch (drawMode) {
			case POINTS:
				mode = GL_POINTS;
				break;
			case TRIANGLES:
				mode = GL_TRIANGLES;
				break;
			case TRIANGLE_STRIP:
				mode = GL_TRIANGLE_STRIP;
				break;
		}
		return mode;
	}

	GLenum convertPolyMode(PolyMode polyMode) {
		GLenum mode;
		switch (polyMode) {
			case FILL:
				mode = GL_FILL;
				break;
			case LINE:
				mode = GL_LINE;
				break;
			case POINT:
				mode = GL_POINT;
				break;
		}
		return mode;
	}

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
			DrawMode drawMode,
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
				convertDrawMode(drawMode),
				reinterpret_cast<GLsizei *>(indicesCount),
				GL_UNSIGNED_INT,
				pointers.data(),
				static_cast<GLsizei>(meshCount),
				reinterpret_cast<GLint *>(vertexOffset)
		);
		GLErrorHandler::checkOpenGLError();
	}

	void OpenGLDrawUtils::setPolygonMode(cookie::PolyMode mode) const {
		glPolygonMode(GL_FRONT_AND_BACK, convertPolyMode(mode));
	}

	OpenGLDrawUtils::OpenGLDrawUtils() = default;
}

#endif