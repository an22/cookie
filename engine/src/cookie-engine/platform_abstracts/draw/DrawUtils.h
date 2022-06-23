//
// Created by Antiufieiev Michael on 08.08.2021.
//

#ifndef COOKIE_ENGINE_DRAWUTILS_H
#define COOKIE_ENGINE_DRAWUTILS_H

#include <cstdint>

namespace cookie {

	enum PolyMode {
		FILL = 0,
		LINE = 1,
		POINT = 2
	};
	enum DrawMode {
		POINTS = 0,
		TRIANGLES = 1,
		TRIANGLE_STRIP = 2
	};

	class DrawUtils {
	public:
		virtual bool shouldCloseWindow() const = 0;
		virtual void clearBuffers() const = 0;
		virtual void swapBuffers() const = 0;
		virtual void enableDepthTest() const = 0;
		virtual void drawInstanced(int32_t first, int32_t size, int32_t times) const = 0;
		virtual void drawMultiElementsWithIndexOffset(
				DrawMode drawMode,
				uint32_t meshCount,
				int32_t *startOffset, //should be marked const but on linux with opengl it won't compile because api require non-const argument
				int32_t *size, //should be marked const but on linux with opengl it won't compile because api require non-const argument
				int32_t *indicesOffset //should be marked const but on linux with opengl it won't compile because api require non-const argument
		) const = 0;
		virtual void drawArrays(int32_t from, int32_t to) const = 0;
		virtual void drawElements(int32_t size) const = 0;
		virtual void cullFace() const = 0;
		virtual void setViewport(int32_t width, int32_t height) const = 0;
		virtual void setPolygonMode(PolyMode mode) const = 0;
		DrawUtils() = default;
		virtual ~DrawUtils() = default;
	};
}

#endif //COOKIE_ENGINE_DRAWUTILS_H
