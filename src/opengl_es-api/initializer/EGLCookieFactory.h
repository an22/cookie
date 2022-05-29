//
// Created by Michael on 1/4/2022.
//

#ifndef COOKIE_ENGINE_EGLCOOKIEFACTORY_H
#define COOKIE_ENGINE_EGLCOOKIEFACTORY_H

#if COOKIE_EGL

#include "CookieFactory.hpp"

namespace cookie {
	class EGLCookieFactory : public cookie::CookieFactory {

	public:
		explicit EGLCookieFactory(CgAPI api);
		~EGLCookieFactory() override = default;
		[[nodiscard]] std::unique_ptr<cookie::Time> provideTimeManagerImpl() const override;
		[[nodiscard]] std::unique_ptr<cookie::Shader> provideShaderImpl(
				const std::string &vertexPath,
				const std::string &fragmentPath
		) const override;
		[[nodiscard]] std::unique_ptr<cookie::BufferStorage> provideBufferStorageImpl() const override;
		[[nodiscard]] std::unique_ptr<cookie::Initializer> provideInitializerImpl() const override;
		[[nodiscard]] std::unique_ptr<cookie::DrawUtils> provideDrawUtilsImpl() const override;
		[[nodiscard]] std::unique_ptr<cookie::PlatformSpecificBufferData> provideBufferDataImpl(cookie::BufferType bufferType) const override;
		[[nodiscard]] std::unique_ptr<cookie::PlatformSpecificData> createPlatformSpecificContainerImpl() const override;
		[[nodiscard]] std::unique_ptr<cookie::TextureProcessor> provideTextureProcessorImpl() const override;
		[[nodiscard]] std::unique_ptr<cookie::GlobalBufferStorage> provideGlobalBufferStorageImpl() const override;
	};
}

#endif
#endif //COOKIE_ENGINE_EGLCOOKIEFACTORY_H
