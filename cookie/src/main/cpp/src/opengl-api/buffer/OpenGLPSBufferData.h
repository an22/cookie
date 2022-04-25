//
// Created by Antiufieiev Michael on 08.08.2021.
//

#ifndef COOKIE_ENGINE_OPENGLPSBUFFERDATA_H
#define COOKIE_ENGINE_OPENGLPSBUFFERDATA_H

#include "PlatformSpecificBufferData.h"
#include <GLES3/gl3.h>

struct OpenGLPSBufferData : public cookie::PlatformSpecificBufferData {
	GLenum usage;
	GLenum target;

	explicit OpenGLPSBufferData(cookie::BufferType bufferType);
};

#endif //COOKIE_ENGINE_OPENGLPSBUFFERDATA_H
