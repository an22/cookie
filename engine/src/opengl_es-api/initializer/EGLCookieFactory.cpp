//
// Created by Michael on 1/4/2022.
//
#include "config.hpp"

#if COOKIE_EGL

#include "EGLCookieFactory.h"
#include "EGLInitializer.hpp"
#include "EGLPlatformSpecificData.h"
#include "EGLBufferStorage.hpp"
#include "EGLDrawUtils.h"
#include "EGLPSBufferData.h"
#include "EGLTextureProcessor.hpp"
#include "EGLGlobalBufferStorage.hpp"
#include "EGLShader.hpp"
#include "EGLTime.hpp"

namespace cookie {
	std::unique_ptr<cookie::Time> EGLCookieFactory::provideTimeManagerImpl() const {
		return std::unique_ptr<cookie::Time>(new EGLTime());
	}

	std::unique_ptr<cookie::Shader> EGLCookieFactory::provideShaderImpl(
			const std::string &vertexPath,
			const std::string &fragmentPath
	) const {
		return std::unique_ptr<cookie::Shader>(new EGLShader(vertexPath, fragmentPath));
	}

	std::unique_ptr<cookie::BufferStorage> EGLCookieFactory::provideBufferStorageImpl() const {
		return std::unique_ptr<cookie::BufferStorage>(new EGLBufferStorage());
	}

	std::unique_ptr<cookie::Initializer> EGLCookieFactory::provideInitializerImpl() const {
		return std::unique_ptr<cookie::Initializer>(new EGLInitializer());
	}

	std::unique_ptr<cookie::DrawUtils> EGLCookieFactory::provideDrawUtilsImpl() const {
		return std::unique_ptr<cookie::DrawUtils>(new EGLDrawUtils());
	}

	std::unique_ptr<cookie::PlatformSpecificBufferData> EGLCookieFactory::provideBufferDataImpl(
			cookie::BufferType bufferType
	) const {
		return std::unique_ptr<cookie::PlatformSpecificBufferData>(new EGLPSBufferData(bufferType));
	}

	std::unique_ptr<cookie::PlatformSpecificData> EGLCookieFactory::createPlatformSpecificContainerImpl() const {
		return std::unique_ptr<cookie::PlatformSpecificData>(new EGLPlatformSpecificData());
	}

	std::unique_ptr<cookie::TextureProcessor> EGLCookieFactory::provideTextureProcessorImpl() const {
		return std::unique_ptr<cookie::TextureProcessor>(new EGLTextureProcessor());
	}

	std::unique_ptr<cookie::GlobalBufferStorage> EGLCookieFactory::provideGlobalBufferStorageImpl() const {
		return std::unique_ptr<cookie::GlobalBufferStorage>(new EGLGlobalBufferStorage());
	}

	EGLCookieFactory::EGLCookieFactory(CgAPI api) : CookieFactory(api) {

	}
}

#endif
