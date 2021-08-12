//
//  OpenGLInitializer.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#ifndef OpenGLInitializer_hpp
#define OpenGLInitializer_hpp

#include "platform_abstracts/Initializer.hpp"

class OpenGLInitializer : public cookie::Initializer {
    void initGraphicsAPIResources() const override;
    void destroyGraphicsAPIResources() const override;
};

#endif /* OpenGLInitializer_hpp */
