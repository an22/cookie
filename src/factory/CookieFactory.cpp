//
//  CookieFactory.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include "Util.h"
#include "OpenGLCookieFactory.h"

namespace cookie {

	std::unique_ptr<CookieFactory> CookieFactory::instance;
	std::mutex CookieFactory::mutex;

	CookieFactory &CookieFactory::getFactory(CgAPI api) {
		std::lock_guard<std::mutex> lock(mutex);
		if (instance == nullptr) {
			switch (api) {

				case CgAPI::OpenGL:
					instance = std::unique_ptr<CookieFactory>(new OpenGLCookieFactory(api));
					break;
					//TODO case Vulkan:
					//TODO case DirectX:
				default:
					cookie::throwAPIUnsupported();
			}
		}
		return *instance;
	}

	CookieFactory::CookieFactory(CgAPI api) {
		cgApi = api;
	}

	std::unique_ptr<cookie::Time> CookieFactory::provideTimeManager() {
		return getFactory().provideTimeManagerImpl();
	}

	std::unique_ptr<cookie::Shader> CookieFactory::provideShader(const std::string &vertexPath, const std::string &fragmentPath) {
		return getFactory().provideShaderImpl(vertexPath, fragmentPath);
	}

	std::unique_ptr<cookie::BufferStorage> CookieFactory::provideBufferStorage() {
		return getFactory().provideBufferStorageImpl();
	}

	std::unique_ptr<cookie::Initializer> CookieFactory::provideInitializer() {
		return getFactory().provideInitializerImpl();
	}

	std::unique_ptr<cookie::DrawUtils> CookieFactory::provideDrawUtils() {
		return getFactory().provideDrawUtilsImpl();
	}

	std::unique_ptr<cookie::PlatformSpecificBufferData> CookieFactory::provideBufferData(cookie::BufferType bufferType) {
		return getFactory().provideBufferDataImpl(bufferType);
	}

	std::unique_ptr<cookie::PlatformSpecificData> CookieFactory::createPlatformSpecificContainer() {
		return getFactory().createPlatformSpecificContainerImpl();
	}

	std::unique_ptr<cookie::TextureProcessor> CookieFactory::provideTextureProcessor() {
		return getFactory().provideTextureProcessorImpl();
	}

	std::unique_ptr<cookie::CrossBatchBufferStorage> CookieFactory::provideCrossBatchBufferStorage() {
		return getFactory().provideCrossBatchBufferStorageImpl();
	}
}
