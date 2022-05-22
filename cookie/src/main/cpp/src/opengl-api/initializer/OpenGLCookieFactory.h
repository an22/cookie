//
// Created by Michael on 1/4/2022.
//

#ifndef COOKIE_ENGINE_OPENGLCOOKIEFACTORY_H
#define COOKIE_ENGINE_OPENGLCOOKIEFACTORY_H

#include "CookieFactory.hpp"
namespace cookie {
	class OpenGLCookieFactory : public cookie::CookieFactory {

	public:
		explicit OpenGLCookieFactory(CgAPI api);
		~OpenGLCookieFactory() override = default;
		std::unique_ptr<cookie::Time> provideTimeManagerImpl() const override;
		std::unique_ptr<cookie::Shader> provideShaderImpl(
				const std::string &vertexPath,
				const std::string &fragmentPath
		) const override;
		std::unique_ptr<cookie::BufferStorage> provideBufferStorageImpl() const override;
		std::unique_ptr<cookie::Initializer> provideInitializerImpl() const override;
		std::unique_ptr<cookie::DrawUtils> provideDrawUtilsImpl() const override;
		std::unique_ptr<cookie::PlatformSpecificBufferData> provideBufferDataImpl(cookie::BufferType bufferType) const override;
		std::unique_ptr<cookie::PlatformSpecificData> createPlatformSpecificContainerImpl() const override;
		std::unique_ptr<cookie::TextureProcessor> provideTextureProcessorImpl() const override;
		std::unique_ptr<cookie::GlobalBufferStorage> provideGlobalBufferStorageImpl() const override;
	};
}

#endif //COOKIE_ENGINE_OPENGLCOOKIEFACTORY_H
