//
// Created by Antiufieiev Michael on 08.08.2021.
//

#include "OpenGLDrawUtils.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Cookie.hpp"
#include "OpenGLPlatformSpecificData.h"

bool OpenGLDrawUtils::shouldCloseWindow() {
    auto &platformData = dynamic_cast<OpenGLPlatformSpecificData &>(*cookie::engine->platformData);
    return glfwWindowShouldClose(platformData.getWindow());
}
void OpenGLDrawUtils::clearBuffers() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
}
void OpenGLDrawUtils::listenInputEvents() {
    auto &platformData = dynamic_cast<OpenGLPlatformSpecificData &>(*cookie::engine->platformData);
    glfwSwapBuffers(platformData.getWindow());
}
void OpenGLDrawUtils::swapBuffers() {
    glfwPollEvents();
}
void OpenGLDrawUtils::enableDepthTest() {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}
void OpenGLDrawUtils::drawInstanced(int32_t first, int32_t size, int32_t times) {
    glDrawArraysInstanced(GL_TRIANGLES, first, size, times);
}
void OpenGLDrawUtils::drawArrays(int32_t from, int32_t to) {
    glDrawArrays(GL_TRIANGLES, from, to);
}
void OpenGLDrawUtils::drawElements(uint32_t size) {
    glDrawElementsInstanced(GL_TRIANGLES, size, GL_UNSIGNED_INT, nullptr, 100000);
}
void OpenGLDrawUtils::cullFace() {
    glEnable(GL_CULL_FACE);
}
