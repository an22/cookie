//
//  OpenGLPlatformSpecificData.h
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#ifndef OpenGLPlatformSpecificData_hpp
#define OpenGLPlatformSpecificData_hpp

#include "platform_abstracts/PlatformSpecificData.hpp"
#include "GLFW/glfw3.h"

class OpenGLPlatformSpecificData : public cookie::PlatformSpecificData {

private:
    GLFWwindow *window = nullptr;
public:
    int32_t width() override;
    int32_t height() override;

    GLFWwindow *getWindow();
    void setWindow(GLFWwindow *window);
    OpenGLPlatformSpecificData() = default;
    ~OpenGLPlatformSpecificData() override;
};

#endif /* OpenGLPlatformSpecificData_hpp */
