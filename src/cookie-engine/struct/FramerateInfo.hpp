//
//  FramerateInfo.h
//  cookie-engine
//
//  Created by Antiufieiev Michael on 01.07.2021.
//

#ifndef FramerateInfo_hpp
#define FramerateInfo_hpp

#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include "platform_abstracts/Time.hpp"

namespace cookie {

	class FramerateInfo {
	private:
		std::unique_ptr<Time> time;

	public:
		unsigned int framerate;
		double framerateTimestamp;
		double frameTime;
		double lastTimestamp;

		FramerateInfo();
		void invalidateFrameRate();
	};
}

#endif /* FramerateInfo_hpp */
