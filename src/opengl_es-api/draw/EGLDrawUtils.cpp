//
// Created by Antiufieiev Michael on 08.08.2021.
//
#include "config.hpp"

#if COOKIE_EGL

#include "EGLErrorHandler.hpp"
#include <GLES3/gl32.h>
#include "EGLDrawUtils.h"
#include "Cookie.hpp"
#include "EGLPlatformSpecificData.h"

namespace cookie {
	bool EGLDrawUtils::shouldCloseWindow() const {
		return false;
	}

	void EGLDrawUtils::clearBuffers() const {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void EGLDrawUtils::swapBuffers() const {
		auto &platformData = cookie::Cookie::getInstance().getPlatformData<EGLPlatformSpecificData>();
		if (!eglSwapBuffers(platformData.getDisplay(), platformData.getSurface())) {
			EGLErrorHandler::checkOpenGLError();
			throw std::runtime_error("CANT SWAP BUFFERS");
		}
	}

	void EGLDrawUtils::enableDepthTest() const {
		glEnable(GL_DEPTH_TEST);
	}

	void EGLDrawUtils::drawInstanced(int32_t first, int32_t size, int32_t times) const {
		glDrawArraysInstanced(GL_TRIANGLES, first, size, times);
	}

	void EGLDrawUtils::drawArrays(int32_t from, int32_t to) const {
		glDrawArrays(GL_TRIANGLES, from, to);
	}

	void EGLDrawUtils::drawElements(int32_t size) const {
		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, nullptr);
	}

	void EGLDrawUtils::cullFace() const {
		glEnable(GL_CULL_FACE);
	}

	void EGLDrawUtils::setViewport(int32_t width, int32_t height) const {
		glViewport(0, 0, width, height);
	}

	void EGLDrawUtils::drawMultiElementsWithIndexOffset(
			uint32_t meshCount,
			int32_t *startOffset,
			int32_t *indicesCount,
			int32_t *vertexOffset
	) const {
		for (int i = 0; i < meshCount; i++) {
			glDrawElementsBaseVertex(
					GL_TRIANGLES,
					indicesCount[i],
					GL_UNSIGNED_INT,
					reinterpret_cast<void *>(startOffset[i]),
					vertexOffset[i]
			);
		}
		EGLErrorHandler::checkOpenGLError();
	}

	EGLDrawUtils::EGLDrawUtils() = default;
}

#endif