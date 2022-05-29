//
//  EGLPlatformSpecificData.h
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#ifndef EGLPlatformSpecificData_hpp
#define EGLPlatformSpecificData_hpp
#if COOKIE_EGL
#include "platform_abstracts/PlatformSpecificData.hpp"
#include "EGL/egl.h"

namespace cookie {
	class EGLPlatformSpecificData : public cookie::PlatformSpecificData {

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
		EGLPlatformSpecificData() = default;
		~EGLPlatformSpecificData() override;
	};
}
#endif
#endif /* EGLPlatformSpecificData_hpp */
