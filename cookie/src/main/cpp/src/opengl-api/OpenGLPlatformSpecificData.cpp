//
//  OpenGLPlatformSpecificData.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include "OpenGLPlatformSpecificData.h"

namespace cookie {

	EGLNativeWindowType OpenGLPlatformSpecificData::getWindow() {
		return window;
	}

	void OpenGLPlatformSpecificData::setWindow(EGLNativeWindowType newWindow) {
		window = newWindow;
	}

	EGLDisplay OpenGLPlatformSpecificData::getDisplay() const {
		return display;
	}

	void OpenGLPlatformSpecificData::setDisplay(EGLDisplay display) {
		OpenGLPlatformSpecificData::display = display;
	}

	EGLSurface OpenGLPlatformSpecificData::getSurface() const {
		return surface;
	}

	void OpenGLPlatformSpecificData::setSurface(EGLSurface surface) {
		OpenGLPlatformSpecificData::surface = surface;
	}

	EGLContext OpenGLPlatformSpecificData::getContext() const {
		return context;
	}

	void OpenGLPlatformSpecificData::setContext(EGLContext context) {
		OpenGLPlatformSpecificData::context = context;
	}

	OpenGLPlatformSpecificData::~OpenGLPlatformSpecificData() = default;
}