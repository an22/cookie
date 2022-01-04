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
#include "TextureProcessor.hpp"
#include "DrawUtils.h"
#include "Time.hpp"
#include "Shader.hpp"
#include "BufferStorage.hpp"
#include "Initializer.hpp"
#include "PlatformSpecificBufferData.h"
#include "PlatformSpecificData.hpp"
#include "CrossBatchBufferStorage.hpp"
#include "CgAPI.h"

namespace cookie {
	class CookieFactory {

	private:
		CgAPI cgApi;

		static std::unique_ptr<CookieFactory> instance;
		static std::mutex mutex;

	protected:
		[[nodiscard]] virtual std::unique_ptr<cookie::Time> provideTimeManagerImpl() const = 0;
		[[nodiscard]] virtual std::unique_ptr<cookie::Shader> provideShaderImpl(
				const std::string &vertexPath,
				const std::string &fragmentPath
		) const = 0;
		[[nodiscard]] virtual std::unique_ptr<cookie::BufferStorage> provideBufferStorageImpl() const = 0;
		[[nodiscard]] virtual std::unique_ptr<cookie::Initializer> provideInitializerImpl() const = 0;
		[[nodiscard]] virtual std::unique_ptr<cookie::DrawUtils> provideDrawUtilsImpl() const = 0;
		[[nodiscard]] virtual std::unique_ptr<cookie::PlatformSpecificBufferData>provideBufferDataImpl(cookie::BufferType bufferType) const = 0;
		[[nodiscard]] virtual std::unique_ptr<cookie::PlatformSpecificData> createPlatformSpecificContainerImpl() const = 0;
		[[nodiscard]] virtual std::unique_ptr<cookie::TextureProcessor> provideTextureProcessorImpl() const = 0;
		[[nodiscard]] virtual std::unique_ptr<cookie::CrossBatchBufferStorage> provideCrossBatchBufferStorageImpl() const = 0;

	public:
		static CookieFactory &getFactory(CgAPI api = CgAPI::OpenGL);

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
		static std::unique_ptr<cookie::PlatformSpecificBufferData> provideBufferData(cookie::BufferType bufferType);
		static std::unique_ptr<cookie::PlatformSpecificData> createPlatformSpecificContainer();
		static std::unique_ptr<cookie::TextureProcessor> provideTextureProcessor();
		static std::unique_ptr<cookie::CrossBatchBufferStorage> provideCrossBatchBufferStorage();
	};
}

#endif /* CookieFactory_hpp */
