//
//  EGLPlatformSpecificData.h
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#ifndef OpenGLPlatformSpecificData_hpp
#define OpenGLPlatformSpecificData_hpp

#if COOKIE_OPENGL

#include <GLFW/glfw3.h>
#include "platform_abstracts/PlatformSpecificData.hpp"

namespace cookie {
	class OpenGLPlatformSpecificData : public cookie::PlatformSpecificData {

	private:
		GLFWwindow *window = nullptr;
	public:
		int32_t width() override;
		int32_t height() override;

		GLFWwindow *getWindow();
		void setWindow(GLFWwindow *newWindow);
		OpenGLPlatformSpecificData() = default;
		~OpenGLPlatformSpecificData() override;
	};
}

#endif
#endif /* OpenGLPlatformSpecificData_hpp */
