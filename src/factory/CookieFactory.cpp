//
//  CookieFactory.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include <stdexcept>
#include "OpenGLDrawUtils.h"
#include "OpenGLPSBufferData.h"
#include "Util.h"
#include "Cookie.hpp"
#include "CookieFactory.hpp"
#include "OpenGLTime.hpp"
#include "OpenGLShader.hpp"
#include "OpenGLBufferStorage.hpp"
#include "OpenGLInitializer.hpp"
#include "OpenGLPlatformSpecificData.h"
#include "OpenGLTextureProcessor.hpp"

std::unique_ptr<cookie::Time> CookieFactory::provideTimeManager() {
	switch (cookie::Cookie::CURRENT_CG_API) {
		case cookie::CgAPI::OpenGL:
			return std::unique_ptr<cookie::Time>(new OpenGLTime());
			//TODO case Vulkan:
			//TODO case DirectX:
		default:
			cookie::throwAPIUnsupported();
	}
}

std::unique_ptr<cookie::Shader> CookieFactory::provideShader(
		const std::string &vertexPath,
		const std::string &fragmentPath
) {
	switch (cookie::Cookie::CURRENT_CG_API) {
		case cookie::CgAPI::OpenGL:
			return std::unique_ptr<cookie::Shader>(new OpenGLShader(vertexPath, fragmentPath));
			//TODO case Vulkan:
			//TODO case DirectX:
		default:
			cookie::throwAPIUnsupported();
	}
}

std::unique_ptr<cookie::BufferStorage> CookieFactory::provideBufferStorage() {
	switch (cookie::Cookie::CURRENT_CG_API) {
		case cookie::CgAPI::OpenGL:
			return std::unique_ptr<cookie::BufferStorage>(new OpenGLBufferStorage());
			//TODO case Vulkan:
			//TODO case DirectX:
		default:
			cookie::throwAPIUnsupported();
	}
}

std::unique_ptr<cookie::Initializer> CookieFactory::provideInitializer() {
	switch (cookie::Cookie::CURRENT_CG_API) {
		case cookie::CgAPI::OpenGL:
			return std::unique_ptr<cookie::Initializer>(new OpenGLInitializer());
			//TODO case Vulkan:
			//TODO case DirectX:
		default:
			cookie::throwAPIUnsupported();
	}
}

std::unique_ptr<cookie::DrawUtils> CookieFactory::provideDrawUtils() {
	switch (cookie::Cookie::CURRENT_CG_API) {
		case cookie::CgAPI::OpenGL:
			return std::unique_ptr<cookie::DrawUtils>(new OpenGLDrawUtils());
			//TODO case Vulkan:
			//TODO case DirectX:
		default:
			cookie::throwAPIUnsupported();
	}
}

std::unique_ptr<cookie::PlatformSpecificData> CookieFactory::createPlatformSpecificContainer() {
	switch (cookie::Cookie::CURRENT_CG_API) {
		case cookie::CgAPI::OpenGL:
			return std::unique_ptr<cookie::PlatformSpecificData>(new OpenGLPlatformSpecificData());
			//TODO case Vulkan:
			//TODO case DirectX:
		default:
			cookie::throwAPIUnsupported();
	}
}

std::unique_ptr<cookie::PlatformSpecificBufferData> CookieFactory::provideBufferData(cookie::BufferType bufferType) {
	switch (cookie::Cookie::CURRENT_CG_API) {
		case cookie::CgAPI::OpenGL:
			return std::unique_ptr<cookie::PlatformSpecificBufferData>(new OpenGLPSBufferData(bufferType));
			//TODO case Vulkan:
			//TODO case DirectX:
		default:
			cookie::throwAPIUnsupported();
	}
}

std::unique_ptr<cookie::TextureProcessor> CookieFactory::provideTextureProcessor() {
	switch (cookie::Cookie::CURRENT_CG_API) {
		case cookie::CgAPI::OpenGL:
			return std::unique_ptr<cookie::TextureProcessor>(new OpenGLTextureProcessor());
			//TODO case Vulkan:
			//TODO case DirectX:
			default:
				cookie::throwAPIUnsupported();
	}
}
