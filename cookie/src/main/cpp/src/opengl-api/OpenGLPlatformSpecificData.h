//
//  OpenGLPlatformSpecificData.h
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#ifndef OpenGLPlatformSpecificData_hpp
#define OpenGLPlatformSpecificData_hpp

#include "platform_abstracts/PlatformSpecificData.hpp"
#include "EGL/egl.h"
namespace cookie {
	class OpenGLPlatformSpecificData : public cookie::PlatformSpecificData {

	private:
		EGLNativeWindowType window = nullptr;
		EGLDisplay display = nullptr;
		EGLSurface surface = nullptr;
		EGLContext context = nullptr;
	public:
		EGLDisplay getDisplay() const;
		void setDisplay(EGLDisplay display);
		EGLSurface getSurface() const;
		void setSurface(EGLSurface surface);
		EGLContext getContext() const;
		void setContext(EGLContext context);
		EGLNativeWindowType getWindow();
		void setWindow(EGLNativeWindowType window);
		OpenGLPlatformSpecificData() = default;
		~OpenGLPlatformSpecificData() override;
	};
}

#endif /* OpenGLPlatformSpecificData_hpp */
