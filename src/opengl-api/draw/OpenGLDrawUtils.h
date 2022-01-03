//
// Created by Antiufieiev Michael on 08.08.2021.
//

#ifndef COOKIE_ENGINE_OPENGLDRAWUTILS_H
#define COOKIE_ENGINE_OPENGLDRAWUTILS_H

#include "DrawUtils.h"

class OpenGLDrawUtils : public cookie::DrawUtils {
public:
	[[nodiscard]] bool shouldCloseWindow() const override;
	void clearBuffers() const override;
	void listenInputEvents()const  override;
	void swapBuffers() const override;
	void enableDepthTest() const override;
	void drawInstanced(int32_t first, int32_t size, int32_t times) const override;
	void drawMultiElementsWithIndexOffset(unsigned int meshCount, const int32_t* startOffset ,const int32_t* indicesCount, const int32_t * vertexOffset) const override;
	void drawArrays(int32_t from, int32_t to) const override;
	void drawElements(int32_t size) const override;
	void cullFace() const override;
	OpenGLDrawUtils() = default;
	~OpenGLDrawUtils() override = default;
};


#endif //COOKIE_ENGINE_OPENGLDRAWUTILS_H
