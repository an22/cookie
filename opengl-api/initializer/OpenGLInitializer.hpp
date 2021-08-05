//
//  OpenGLInitializer.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#ifndef OpenGLInitializer_hpp
#define OpenGLInitializer_hpp

#include "Initializer.h"

class OpenGLInitializer : public cookie::Initializer {
	virtual void initGraphicsAPIResources() const override;
	virtual void destroyGraphicsAPIResources() const override;
};

#endif /* OpenGLInitializer_hpp */
