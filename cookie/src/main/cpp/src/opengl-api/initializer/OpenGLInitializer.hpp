//
//  OpenGLInitializer.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#ifndef OpenGLInitializer_hpp
#define OpenGLInitializer_hpp

#include "Initializer.hpp"

class OpenGLInitializer : public cookie::Initializer {
	bool initGraphicsAPIResources(cookie::PlatformSpecificData& data) const override;
	void destroyGraphicsAPIResources(cookie::PlatformSpecificData& data) const override;
};

#endif /* OpenGLInitializer_hpp */