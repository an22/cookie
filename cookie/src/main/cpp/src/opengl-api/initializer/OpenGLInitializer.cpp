//
//  OpenGLInitializer.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <iostream>
#include "OpenGLInitializer.hpp"
#include "OpenGLPlatformSpecificData.h"
#include "Cookie.hpp"

void windowReshapeCallback(EGLNativeWindowType *window, int newWidth, int newHeight) {
	glViewport(0, 0, newWidth, newHeight); // sets screen region associated with framebuffer
	cookie::Cookie::getInstance().getCurrentScene().getSettings().onWindowResized(newWidth, newHeight);
}

void errorCallback(int code, const char *description) {
	//TODO proper error handling
	std::cout << description << std::endl;
}

bool OpenGLInitializer::initGraphicsAPIResources(cookie::PlatformSpecificData &data) const {
	const EGLint attribs[] = {
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_BLUE_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_RED_SIZE, 8,
			EGL_NONE
	};
	auto &platformData = dynamic_cast<OpenGLPlatformSpecificData &>(data);
	EGLDisplay display;
	EGLConfig config;
	EGLint numConfigs;
	EGLint format;
	EGLSurface surface;
	EGLContext context;
	EGLint width;
	EGLint height;

	//LOG_INFO("Initializing context");
	if ((display = eglGetDisplay(EGL_DEFAULT_DISPLAY)) == EGL_NO_DISPLAY) {
		//LOG_ERROR("eglGetDisplay() returned error %d", eglGetError());
		return false;
	}
	if (!eglInitialize(display, nullptr, nullptr)) {
		//LOG_ERROR("eglInitialize() returned error %d", eglGetError());
		return false;
	}

	if (!eglChooseConfig(display, attribs, &config, 1, &numConfigs)) {
		//LOG_ERROR("eglChooseConfig() returned error %d", eglGetError());
		return false;
	}

	if (!eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format)) {
		//LOG_ERROR("eglGetConfigAttrib() returned error %d", eglGetError());
		return false;
	}

	if (!(surface = eglCreateWindowSurface(display, config, platformData.getWindow(), 0))) {
		//LOG_ERROR("eglCreateWindowSurface() returned error %d", eglGetError());
		return false;
	}

	const EGLint attrs[] = {
			EGL_CONTEXT_MAJOR_VERSION, 3,
			EGL_CONTEXT_MINOR_VERSION, 2,
			EGL_NONE
	};
	if (!(context = eglCreateContext(display, config, nullptr, attrs))) {
		//LOG_ERROR("eglCreateContext() returned error %d", eglGetError());
		return false;
	}

	if (!eglMakeCurrent(display, surface, surface, context)) {
		//LOG_ERROR("eglMakeCurrent() returned error %d", eglGetError());
		return false;
	}

	if (!eglQuerySurface(display, surface, EGL_WIDTH, &width) ||
		!eglQuerySurface(display, surface, EGL_HEIGHT, &height)) {
		//LOG_ERROR("eglQuerySurface() returned error %d", eglGetError());
		return false;
	}

	int a[2] = {};

	eglQueryContext(display, context, EGL_CONTEXT_MINOR_VERSION, a);

	platformData.setWidth(width);
	platformData.setHeight(width);
	platformData.setContext(context);
	platformData.setDisplay(display);
	platformData.setSurface(surface);
	eglSwapInterval(display, 1);
	return true;
}

void OpenGLInitializer::destroyGraphicsAPIResources(cookie::PlatformSpecificData &data) const {
	auto &platformData = dynamic_cast<OpenGLPlatformSpecificData &>(data);
	eglMakeCurrent(platformData.getDisplay(), EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglDestroyContext(platformData.getDisplay(), platformData.getContext());
	eglDestroySurface(platformData.getDisplay(), platformData.getSurface());
	eglTerminate(platformData.getWindow());
}
