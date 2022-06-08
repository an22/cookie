//
//  EGLInitializer.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//
#include "config.hpp"

#if COOKIE_EGL

#include <EGL/egl.h>
#include <GLES3/gl32.h>
#include <iostream>
#include "EGLErrorHandler.hpp"
#include "EGLInitializer.hpp"
#include "OpenGLPlatformSpecificData.h"
#include "Cookie.hpp"
#include "Macro.h"

namespace cookie {
	void EGLInitializer::initGraphicsAPIResources(cookie::PlatformSpecificData &data) const {
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
		EGLDisplay display;
		EGLConfig config;
		EGLint numConfigs;
		EGLint format;
		EGLSurface surface;
		EGLContext context;
		EGLint width;
		EGLint height;

		LOG_I("Initializing context");
		if ((display = eglGetDisplay(EGL_DEFAULT_DISPLAY)) == EGL_NO_DISPLAY) {
			throw std::runtime_error("eglGetDisplay(): cannot get display");
		}
		EGLint maj, min;
		if (!eglInitialize(display, &maj, &min)) {
			throw std::runtime_error("eglInitialize(): cannot initialize display");
		}
		if (!eglChooseConfig(display, attribs, &config, 1, &numConfigs)) {
			throw std::runtime_error("eglChooseConfig(): cannot choose display");
		}
		if (!eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format)) {
			throw std::runtime_error("eglGetConfigAttrib(): cannot get config attributes");
		}
		auto &platformData = dynamic_cast<EGLPlatformSpecificData &>(data);
		if (!(surface = eglCreateWindowSurface(
				display,
				config,
				platformData.getWindow(),
				nullptr
		))) {
			throw std::runtime_error("eglCreateWindowSurface(): cannot create window surface");
		}
		const EGLint attrs[] = {
				EGL_CONTEXT_MAJOR_VERSION, 3,
				EGL_CONTEXT_MINOR_VERSION, 2,
				EGL_NONE
		};
		if (!(context = eglCreateContext(display, config, nullptr, attrs))) {
			throw std::runtime_error("eglCreateContext(): cannot create OpenGL ES context");
		}
		if (!eglMakeCurrent(display, surface, surface, context)) {
			throw std::runtime_error("eglMakeCurrent(): cannot make context current");
		}
		if (!eglQuerySurface(display, surface, EGL_WIDTH, &width) ||
			!eglQuerySurface(display, surface, EGL_HEIGHT, &height)) {
			throw std::runtime_error("eglQuerySurface(): cannot query surface parameters");
		}

		platformData.setWidth(width);
		platformData.setHeight(height);
		platformData.setContext(context);
		platformData.setDisplay(display);
		platformData.setSurface(surface);
		eglSwapInterval(display, 1);
		EGLErrorHandler::checkOpenGLError();
	}

	void EGLInitializer::destroyGraphicsAPIResources(cookie::PlatformSpecificData &data) const {
		auto &platformData = dynamic_cast<EGLPlatformSpecificData &>(data);
		eglMakeCurrent(platformData.getDisplay(), EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		eglDestroySurface(platformData.getDisplay(), platformData.getSurface());
		eglDestroyContext(platformData.getDisplay(), platformData.getContext());
		eglTerminate(platformData.getDisplay());
	}
}

#endif