//
// Created by Antiufieiev Michael on 08.08.2021.
//

#ifndef COOKIE_ENGINE_OPENGLDRAWUTILS_H
#define COOKIE_ENGINE_OPENGLDRAWUTILS_H

#if COOKIE_OPENGL

#include <OpenGLPlatformSpecificData.h>
#include "DrawUtils.h"

namespace cookie {
	class OpenGLDrawUtils : public cookie::DrawUtils {
	public:
		[[nodiscard]] bool shouldCloseWindow() const override;
		void clearBuffers() const override;
		void swapBuffers() const override;
		void enableDepthTest() const override;
		void drawInstanced(int32_t first, int32_t size, int32_t times) const override;
		void drawMultiElementsWithIndexOffset(
				DrawMode mode,
				uint32_t meshCount,
				int32_t *startOffset,
				int32_t *indicesCount,
				int32_t *vertexOffset
		) const override;
		void setPolygonMode(cookie::PolyMode mode) const override;
		void drawArrays(int32_t from, int32_t to) const override;
		void drawElements(int32_t size) const override;
		void setViewport(int32_t width, int32_t height) const override;
		void cullFace() const override;
		OpenGLDrawUtils();
		~OpenGLDrawUtils() override = default;
	};
}

#endif
#endif //COOKIE_ENGINE_OPENGLDRAWUTILS_H
