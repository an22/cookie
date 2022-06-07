//
// Created by Antiufieiev Michael on 08.08.2021.
//

#ifndef COOKIE_ENGINE_EGLPSBUFFERDATA_H
#define COOKIE_ENGINE_EGLPSBUFFERDATA_H

#if COOKIE_EGL

#include "PlatformSpecificBufferData.h"
#include <GLES3/gl3.h>

struct EGLPSBufferData : public cookie::PlatformSpecificBufferData {
	GLenum usage;
	GLenum target;

	explicit EGLPSBufferData(cookie::BufferType bufferType);
};

#endif
#endif //COOKIE_ENGINE_EGLPSBUFFERDATA_H
