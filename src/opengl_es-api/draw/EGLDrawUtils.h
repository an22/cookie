//
// Created by Antiufieiev Michael on 08.08.2021.
//

#ifndef COOKIE_ENGINE_EGLDRAWUTILS_H
#define COOKIE_ENGINE_EGLDRAWUTILS_H

#if COOKIE_EGL

#include <OpenGLPlatformSpecificData.h>
#include "DrawUtils.h"
namespace cookie {
	class EGLDrawUtils : public cookie::DrawUtils {
	public:
		[[nodiscard]] bool shouldCloseWindow() const override;
		void clearBuffers() const override;
		void swapBuffers() const override;
		void enableDepthTest() const override;
		void drawInstanced(int32_t first, int32_t size, int32_t times) const override;
		void drawMultiElementsWithIndexOffset(
				unsigned int meshCount,
				const int32_t *startOffset,
				const int32_t *indicesCount,
				const int32_t *vertexOffset
		) const override;
		void drawArrays(int32_t from, int32_t to) const override;
		void drawElements(int32_t size) const override;
		void setViewport(int32_t width, int32_t height) const override;
		void cullFace() const override;
		EGLDrawUtils();
		~EGLDrawUtils() override = default;
	};
}
#endif

#endif //COOKIE_ENGINE_EGLDRAWUTILS_H
