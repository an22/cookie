//
//  CookieFactory.h
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#ifndef CookieFactory_hpp
#define CookieFactory_hpp

#include <memory>
#include <mutex>
#include <glm/glm.hpp>
#include "CgAPI.h"

namespace cookie {

	class FileManager;
	class Time;
	class Shader;
	class BufferStorage;
	class Initializer;
	class DrawUtils;
	class PlatformSpecificBufferData;
	class PlatformSpecificData;
	class TextureProcessor;
	class GlobalBufferStorage;
	class SceneSectorManager;
	struct Bounds;

	class CookieFactory {

	private:
		CgAPI cgApi;

		static std::unique_ptr<CookieFactory> instance;
		static std::mutex mutex;
		static std::unique_ptr<FileManager> fileManager;

	protected:
		[[nodiscard]] virtual std::unique_ptr<cookie::Time> provideTimeManagerImpl() const = 0;
		[[nodiscard]] virtual std::unique_ptr<cookie::Shader> provideShaderImpl(
				const std::string &vertexPath,
				const std::string &fragmentPath
		) const = 0;
		[[nodiscard]] virtual std::unique_ptr<cookie::BufferStorage> provideBufferStorageImpl() const = 0;
		[[nodiscard]] virtual std::unique_ptr<cookie::Initializer> provideInitializerImpl() const = 0;
		[[nodiscard]] virtual std::unique_ptr<cookie::DrawUtils> provideDrawUtilsImpl() const = 0;
		[[nodiscard]] virtual std::unique_ptr<cookie::PlatformSpecificData> createPlatformSpecificContainerImpl() const = 0;
		[[nodiscard]] virtual std::unique_ptr<cookie::TextureProcessor> provideTextureProcessorImpl() const = 0;
		[[nodiscard]] virtual std::unique_ptr<cookie::GlobalBufferStorage> provideGlobalBufferStorageImpl() const = 0;

	public:

		static void init(CgAPI api, std::unique_ptr<FileManager> manager);
		static CookieFactory &getFactory();
		static const FileManager &getManager();
		explicit CookieFactory(CgAPI api);
		virtual ~CookieFactory() = default;
		CookieFactory(CookieFactory &&) = delete;
		CookieFactory(CookieFactory &) = delete;
		CookieFactory &operator=(const CookieFactory &) = delete;

		static std::unique_ptr<cookie::Time> provideTimeManager();
		static std::unique_ptr<cookie::Shader> provideShader(
				const std::string &vertexPath,
				const std::string &fragmentPath
		);
		static std::unique_ptr<cookie::BufferStorage> provideBufferStorage();
		static std::unique_ptr<cookie::Initializer> provideInitializer();
		static std::unique_ptr<cookie::DrawUtils> provideDrawUtils();
		static std::unique_ptr<cookie::PlatformSpecificData> createPlatformSpecificContainer();
		static std::unique_ptr<cookie::TextureProcessor> provideTextureProcessor();
		static std::unique_ptr<cookie::GlobalBufferStorage> provideGlobalBufferStorage();
		static std::unique_ptr<cookie::SceneSectorManager> provideSceneSectorManager(float sectorSize, const Bounds& bounds);
	};
}

#endif /* CookieFactory_hpp */
