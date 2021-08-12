//
// Created by Antiufieiev Michael on 08.08.2021.
//

#ifndef COOKIE_ENGINE_DRAWUTILS_H
#define COOKIE_ENGINE_DRAWUTILS_H

#include <cstdint>

namespace cookie {
    class DrawUtils {
    public:
        virtual bool shouldCloseWindow() = 0;
        virtual void clearBuffers() = 0;
        virtual void listenInputEvents() = 0;
        virtual void swapBuffers() = 0;
        virtual void enableDepthTest() = 0;
        virtual void drawInstanced(int32_t first, int32_t size, int32_t times) = 0;
        virtual void enableVertexAttribute(int32_t attrib) = 0;
        DrawUtils() = default;
        virtual ~DrawUtils() = default;
    };
}

#endif //COOKIE_ENGINE_DRAWUTILS_H
