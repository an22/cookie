//
//  EGLInitializer.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#ifndef EGLInitializer_hpp
#define EGLInitializer_hpp

#if COOKIE_EGL

#include "Initializer.hpp"

namespace cookie {
	class EGLInitializer : public cookie::Initializer {
		void initGraphicsAPIResources(cookie::PlatformSpecificData &data) const override;
		void destroyGraphicsAPIResources(cookie::PlatformSpecificData &data) const override;
	};
}

#endif
#endif /* EGLInitializer_hpp */
