//
//  OpenGLInitializer.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include <EGL/egl.h>
#include <GLES3/gl32.h>
#include <iostream>
#include <android/native_window.h>
#include "GLErrorHandler.hpp"
#include "OpenGLInitializer.hpp"
#include "OpenGLPlatformSpecificData.h"
#include "Cookie.hpp"

void windowReshapeCallback(EGLNativeWindowType *window, int newWidth, int newHeight) {
	glViewport(0, 0, newWidth, newHeight); // sets screen region associated with framebuffer
	cookie::Cookie::getInstance().getCurrentScene()
								 .getSettings()
								 .onWindowResized(newWidth, newHeight);
}

void errorCallback(int code, const char *description) {
	//TODO proper error handling
	std::cout << description << std::endl;
}

bool OpenGLInitializer::initGraphicsAPIResources(cookie::PlatformSpecificData &data) const {
	GLErrorHandler handler;
	const EGLint attribs[] = {
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_CONFIG_CAVEAT, EGL_NONE,
			EGL_BUFFER_SIZE, 16,
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
	EGLint maj, min;
	if (!eglInitialize(display, &maj, &min)) {
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
	if (!eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT)) {

		throw std::runtime_error("eglMakeCurrent() failed");
	}
	if (!eglMakeCurrent(display, surface, surface, context)) {
		//LOG_ERROR("eglMakeCurrent() returned error %d", eglGetError());
		return false;
	}
	handler.checkOpenGLError();
	if (!eglQuerySurface(display, surface, EGL_WIDTH, &width) ||
		!eglQuerySurface(display, surface, EGL_HEIGHT, &height)) {
		//LOG_ERROR("eglQuerySurface() returned error %d", eglGetError());
		return false;
	}
	handler.checkOpenGLError();
	glDisable(GL_DITHER);

	platformData.setWidth(width);
	platformData.setHeight(height);
	platformData.setContext(context);
	platformData.setDisplay(display);
	platformData.setSurface(surface);
	eglSwapInterval(display, 1);
	handler.checkOpenGLError();
	return true;
}

void OpenGLInitializer::destroyGraphicsAPIResources(cookie::PlatformSpecificData &data) const {
	auto &platformData = dynamic_cast<OpenGLPlatformSpecificData &>(data);
	eglMakeCurrent(platformData.getDisplay(), EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglDestroyContext(platformData.getDisplay(), platformData.getContext());
	eglDestroySurface(platformData.getDisplay(), platformData.getSurface());
	eglTerminate(platformData.getWindow());
}
