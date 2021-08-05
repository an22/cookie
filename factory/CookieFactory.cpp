//
//  CookieFactory.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include <exception>
#include "Cookie.h"
#include "CookieFactory.h"
#include "OpenGLTime.hpp"
#include "OpenGLShader.hpp"
#include "OpenGLBufferStorage.hpp"
#include "OpenGLInitializer.hpp"
#include "OpenGLPlatformSpecificData.h"

std::unique_ptr<cookie::Time> CookieFactory::provideTimeManager() {
	switch (cookie::engine->CURRENT_CG_API) {
		case cookie::CgAPI::OpenGL:
			return std::unique_ptr<cookie::Time>(new OpenGLTime());
			//TODO case Vulkan:
			//TODO case DirectX:
		default: throw std::invalid_argument("Selected Rendering API isn't supported");
	}
}

std::unique_ptr<cookie::Shader> CookieFactory::provideShader(const std::string& vertexPath, const std::string& fragmentPath) {
	switch (cookie::engine->CURRENT_CG_API) {
		case cookie::CgAPI::OpenGL:
			return std::unique_ptr<cookie::Shader>(new OpenGLShader(vertexPath, fragmentPath));
			//TODO case Vulkan:
			//TODO case DirectX:
		default: throw std::invalid_argument("Selected Rendering API isn't supported");
	}
}

std::unique_ptr<cookie::BufferStorage> CookieFactory::provideBufferStorage(size_t bufferSize) {
	switch (cookie::engine->CURRENT_CG_API) {
		case cookie::CgAPI::OpenGL:
			return std::unique_ptr<cookie::BufferStorage>(new OpenGLBufferStorage(bufferSize));
			//TODO case Vulkan:
			//TODO case DirectX:
		default: throw std::invalid_argument("Selected Rendering API isn't supported");
	}
}

std::unique_ptr<cookie::Initializer> CookieFactory::provideInitializer() {
	switch (cookie::engine->CURRENT_CG_API) {
		case cookie::CgAPI::OpenGL:
			return std::unique_ptr<cookie::Initializer>(new OpenGLInitializer());
			//TODO case Vulkan:
			//TODO case DirectX:
		default: throw std::invalid_argument("Selected Rendering API isn't supported");
	}
}

std::unique_ptr<cookie::PlatformSpecificData> CookieFactory::createPlatformSpecificContainer() {
	switch (cookie::engine->CURRENT_CG_API) {
		case cookie::CgAPI::OpenGL:
			return std::unique_ptr<cookie::PlatformSpecificData>(new OpenGLPlatformSpecificData());
			//TODO case Vulkan:
			//TODO case DirectX:
		default: throw std::invalid_argument("Selected Rendering API isn't supported");
	}
}
