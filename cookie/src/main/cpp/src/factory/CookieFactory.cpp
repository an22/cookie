//
//  CookieFactory.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include "Util.h"
#include "OpenGLCookieFactory.h"
#include "CookieFactory.hpp"

#include <memory>

namespace cookie {

	std::unique_ptr<CookieFactory> CookieFactory::instance;
	std::mutex CookieFactory::mutex;
	std::unique_ptr<FileManager> CookieFactory::fileManager;

	void CookieFactory::init(CgAPI api, std::unique_ptr<FileManager> manager) {
		std::lock_guard<std::mutex> lock(mutex);
		fileManager = std::move(manager);
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

	CookieFactory &CookieFactory::getFactory() {
		std::lock_guard<std::mutex> lock(mutex);
		return *instance;
	}

	const FileManager &CookieFactory::getManager() {
		return *fileManager;
	}

	CookieFactory::CookieFactory(CgAPI api) {
		cgApi = api;
	}

	std::unique_ptr<cookie::Time> CookieFactory::provideTimeManager() {
		return getFactory().provideTimeManagerImpl();
	}

	std::unique_ptr<cookie::Shader>
	CookieFactory::provideShader(const std::string &vertexPath, const std::string &fragmentPath) {
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

	std::unique_ptr<cookie::PlatformSpecificBufferData>
	CookieFactory::provideBufferData(cookie::BufferType bufferType) {
		return getFactory().provideBufferDataImpl(bufferType);
	}

	std::unique_ptr<cookie::PlatformSpecificData> CookieFactory::createPlatformSpecificContainer() {
		return getFactory().createPlatformSpecificContainerImpl();
	}

	std::unique_ptr<cookie::TextureProcessor> CookieFactory::provideTextureProcessor() {
		return getFactory().provideTextureProcessorImpl();
	}

	std::unique_ptr<cookie::GlobalBufferStorage> CookieFactory::provideGlobalBufferStorage() {
		return getFactory().provideGlobalBufferStorageImpl();
	}

	std::unique_ptr<cookie::SceneSectorManager> CookieFactory::provideSceneSectorManager(
			float sectorSize,
			const glm::vec4 &bounds
	) {
		return std::make_unique<cookie::SceneSectorManager>(sectorSize, bounds);
	}
}
