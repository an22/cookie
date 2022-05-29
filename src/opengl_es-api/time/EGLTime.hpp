//
//  EGLTime.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#ifndef EGLTime_hpp
#define EGLTime_hpp

#if COOKIE_EGL

#include "platform_abstracts/Time.hpp"

namespace cookie {
	class EGLTime : public cookie::Time {

	public:
		double getFrameTime() override;
		~EGLTime() override = default;
	};
}

#endif
#endif /* EGLTime_hpp */
