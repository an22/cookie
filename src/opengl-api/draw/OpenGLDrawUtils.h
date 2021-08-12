//
// Created by Antiufieiev Michael on 08.08.2021.
//

#ifndef COOKIE_ENGINE_OPENGLDRAWUTILS_H
#define COOKIE_ENGINE_OPENGLDRAWUTILS_H

#include "DrawUtils.h"

class OpenGLDrawUtils : public cookie::DrawUtils {
public:
    bool shouldCloseWindow() override;
    void clearBuffers() override;
    void listenInputEvents() override;
    void swapBuffers() override;
    void enableDepthTest() override;
    void drawInstanced(int32_t first, int32_t size, int32_t times) override;
    void enableVertexAttribute(int32_t attrib) override;
    OpenGLDrawUtils() = default;
    ~OpenGLDrawUtils() override = default;

};


#endif //COOKIE_ENGINE_OPENGLDRAWUTILS_H
