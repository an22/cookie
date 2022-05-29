//
//  OpenGLTime.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#ifndef OpenGLTime_hpp
#define OpenGLTime_hpp

#if COOKIE_OPENGL

#include "platform_abstracts/Time.hpp"

namespace cookie {
	class OpenGLTime : public cookie::Time {

	public:
		double getFrameTime() override;
		~OpenGLTime() override = default;
	};
}

#endif
#endif /* OpenGLTime_hpp */
