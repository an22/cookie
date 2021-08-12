//
//  CookieFactory.h
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#ifndef CookieFactory_hpp
#define CookieFactory_hpp

#include <memory>
#include "DrawUtils.h"
#include "Time.hpp"
#include "Shader.hpp"
#include "BufferStorage.hpp"
#include "Initializer.hpp"
#include "PlatformSpecificBufferData.h"
#include "PlatformSpecificData.hpp"

class CookieFactory {

public:
    static std::unique_ptr<cookie::Time> provideTimeManager();
    static std::unique_ptr<cookie::Shader> provideShader(
            const std::string &vertexPath,
            const std::string &fragmentPath
    );
    static std::unique_ptr<cookie::BufferStorage> provideBufferStorage(size_t bufferSize);
    static std::unique_ptr<cookie::Initializer> provideInitializer();
    static std::unique_ptr<cookie::DrawUtils> provideDrawUtils();
    static std::unique_ptr<cookie::PlatformSpecificBufferData> provideBufferData(cookie::BufferType bufferType);
    static std::unique_ptr<cookie::PlatformSpecificData> createPlatformSpecificContainer();
};

#endif /* CookieFactory_hpp */
