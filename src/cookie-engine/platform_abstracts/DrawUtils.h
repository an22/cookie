//
// Created by Antiufieiev Michael on 08.08.2021.
//

#ifndef COOKIE_ENGINE_DRAWUTILS_H
#define COOKIE_ENGINE_DRAWUTILS_H

#include <cstdint>

namespace cookie {
    class DrawUtils {
    public:
        virtual bool shouldCloseWindow() const = 0;
        virtual void clearBuffers() const = 0;
        virtual void listenInputEvents() const = 0;
        virtual void swapBuffers() const = 0;
        virtual void enableDepthTest() const  = 0;
        virtual void drawInstanced(int32_t first, int32_t size, int32_t times) const = 0;
        virtual void drawArrays(int32_t from, int32_t to) const = 0;
        virtual void drawElements(unsigned int size) const = 0 ;
        virtual void cullFace() const = 0;
        DrawUtils() = default;
        virtual ~DrawUtils() = default;
    };
}

#endif //COOKIE_ENGINE_DRAWUTILS_H
