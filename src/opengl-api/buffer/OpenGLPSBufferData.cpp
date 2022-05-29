//
// Created by Antiufieiev Michael on 08.08.2021.
//
#include "config.hpp"

#if COOKIE_OPENGL

#include "OpenGLPSBufferData.h"

OpenGLPSBufferData::OpenGLPSBufferData(cookie::BufferType bufferType) {
	switch (bufferType) {

		case cookie::BufferType::VERTEX_BUFFER: {
			usage = GL_STATIC_DRAW;
			target = GL_ARRAY_BUFFER;
			break;
		}
	}
}
#endif
