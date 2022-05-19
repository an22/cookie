//
// Created by Michael on 1/4/2022.
//

#include <OpenGlGlobalBufferStorage.hpp>
#include <OpenGLTextureProcessor.hpp>
#include <OpenGLPSBufferData.h>
#include <OpenGLPlatformSpecificData.h>
#include <OpenGLDrawUtils.h>
#include <OpenGLTime.hpp>
#include <OpenGLShader.hpp>
#include <OpenGLBufferStorage.hpp>
#include "OpenGLCookieFactory.h"
#include "OpenGLInitializer.hpp"

std::unique_ptr<cookie::Time> OpenGLCookieFactory::provideTimeManagerImpl() const {
	return std::unique_ptr<cookie::Time>(new OpenGLTime());
}

std::unique_ptr<cookie::Shader> OpenGLCookieFactory::provideShaderImpl(const std::string &vertexPath, const std::string &fragmentPath) const {
	return std::unique_ptr<cookie::Shader>(new OpenGLShader(vertexPath, fragmentPath));
}

std::unique_ptr<cookie::BufferStorage> OpenGLCookieFactory::provideBufferStorageImpl() const {
	return std::unique_ptr<cookie::BufferStorage>(new OpenGLBufferStorage());
}

std::unique_ptr<cookie::Initializer> OpenGLCookieFactory::provideInitializerImpl() const {
	return std::unique_ptr<cookie::Initializer>(new OpenGLInitializer());
}

std::unique_ptr<cookie::DrawUtils> OpenGLCookieFactory::provideDrawUtilsImpl() const {
	return std::unique_ptr<cookie::DrawUtils>(new OpenGLDrawUtils());
}

std::unique_ptr<cookie::PlatformSpecificBufferData> OpenGLCookieFactory::provideBufferDataImpl(cookie::BufferType bufferType) const {
	return std::unique_ptr<cookie::PlatformSpecificBufferData>(new OpenGLPSBufferData(bufferType));
}

std::unique_ptr<cookie::PlatformSpecificData> OpenGLCookieFactory::createPlatformSpecificContainerImpl() const {
	return std::unique_ptr<cookie::PlatformSpecificData>(new OpenGLPlatformSpecificData());
}

std::unique_ptr<cookie::TextureProcessor> OpenGLCookieFactory::provideTextureProcessorImpl() const {
	return std::unique_ptr<cookie::TextureProcessor>(new OpenGLTextureProcessor());
}

std::unique_ptr<cookie::GlobalBufferStorage> OpenGLCookieFactory::provideGlobalBufferStorageImpl() const {
	return std::unique_ptr<cookie::GlobalBufferStorage>(new OpenGLGlobalBufferStorage());
}

OpenGLCookieFactory::OpenGLCookieFactory(CgAPI api) : CookieFactory(api) {

}