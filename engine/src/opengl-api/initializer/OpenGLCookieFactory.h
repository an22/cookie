//
// Created by Michael on 1/4/2022.
//

#ifndef COOKIE_ENGINE_OPENGLCOOKIEFACTORY_H
#define COOKIE_ENGINE_OPENGLCOOKIEFACTORY_H

#if COOKIE_OPENGL

#include "CookieFactory.hpp"

namespace cookie {
	class OpenGLCookieFactory : public cookie::CookieFactory {

	public:
		explicit OpenGLCookieFactory(CgAPI api);
		~OpenGLCookieFactory() override = default;
		[[nodiscard]] std::unique_ptr<cookie::Time> provideTimeManagerImpl() const override;
		[[nodiscard]] std::unique_ptr<cookie::Shader> provideShaderImpl(
				const std::string &vertexPath,
				const std::string &fragmentPath
		) const override;
		[[nodiscard]] std::unique_ptr<cookie::BufferStorage> provideBufferStorageImpl() const override;
		[[nodiscard]] std::unique_ptr<cookie::Initializer> provideInitializerImpl() const override;
		[[nodiscard]] std::unique_ptr<cookie::DrawUtils> provideDrawUtilsImpl() const override;
		[[nodiscard]] std::unique_ptr<cookie::PlatformSpecificData>
		createPlatformSpecificContainerImpl() const override;
		[[nodiscard]] std::unique_ptr<cookie::TextureProcessor> provideTextureProcessorImpl() const override;
		[[nodiscard]] std::unique_ptr<cookie::GlobalBufferStorage> provideGlobalBufferStorageImpl() const override;
	};
}

#endif
#endif //COOKIE_ENGINE_OPENGLCOOKIEFACTORY_H
