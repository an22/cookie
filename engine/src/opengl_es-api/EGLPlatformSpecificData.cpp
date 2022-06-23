//
//  EGLPlatformSpecificData.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//
#include "config.hpp"

#if COOKIE_EGL

#include "EGLPlatformSpecificData.h"

namespace cookie {

	EGLNativeWindowType EGLPlatformSpecificData::getWindow() {
		return window;
	}

	void EGLPlatformSpecificData::setWindow(EGLNativeWindowType newWindow) {
		window = newWindow;
	}

	EGLDisplay EGLPlatformSpecificData::getDisplay() const {
		return display;
	}

	void EGLPlatformSpecificData::setDisplay(EGLDisplay display) {
		EGLPlatformSpecificData::display = display;
	}

	EGLSurface EGLPlatformSpecificData::getSurface() const {
		return surface;
	}

	void EGLPlatformSpecificData::setSurface(EGLSurface surface) {
		EGLPlatformSpecificData::surface = surface;
	}

	EGLContext EGLPlatformSpecificData::getContext() const {
		return context;
	}

	void EGLPlatformSpecificData::setContext(EGLContext context) {
		EGLPlatformSpecificData::context = context;
	}

	EGLPlatformSpecificData::~EGLPlatformSpecificData() = default;
}

#endif