//
// Created by Antiufieiev Michael on 08.08.2021.
//

#include "GLErrorHandler.hpp"
#include <GLES3/gl32.h>
#include "OpenGLDrawUtils.h"
#include "Cookie.hpp"
#include "OpenGLPlatformSpecificData.h"

namespace cookie {
	bool OpenGLDrawUtils::shouldCloseWindow() const {
		return false;
	}

	void OpenGLDrawUtils::clearBuffers() const {
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLDrawUtils::swapBuffers() const {
		auto &platformData = cookie::Cookie::getInstance().getPlatformData<OpenGLPlatformSpecificData>();
		if (!eglSwapBuffers(platformData.getDisplay(), platformData.getSurface())) {
			GLErrorHandler::checkOpenGLError();
			throw std::runtime_error("CANT SWAP BUFFERS");
		}
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
			unsigned int meshCount,
			const int32_t *startOffset,
			const int32_t *indicesCount,
			const int32_t *vertexOffset
	) const {
		//glMultiDrawElementsBaseVertex
		/*std::vector<void *> pointers(meshCount);
		for (int i = 0; i < meshCount; i++) {
			pointers[i] = reinterpret_cast<void *>(startOffset[i]);
		}*/
		for (int i = 0; i < meshCount; i++) {
			glDrawElementsBaseVertex(
					GL_TRIANGLES,
					indicesCount[i],
					GL_UNSIGNED_INT,
					reinterpret_cast<void *>(startOffset[i]),
					vertexOffset[i]
			);
		}
		GLErrorHandler::checkOpenGLError();
	}

	OpenGLDrawUtils::OpenGLDrawUtils() = default;
}