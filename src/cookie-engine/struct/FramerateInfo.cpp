//
//  FramerateInfo.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 06.08.2021.
//

#include <iostream>
#include "FramerateInfo.hpp"
#include "CookieFactory.hpp"

namespace cookie {

	FramerateInfo::FramerateInfo() : time(CookieFactory::provideTimeManager()) {
		framerate = 0;
		framerateTimestamp = 0.0;
		frameTime = 0.0;
		lastTimestamp = 0.0;
	}

	void FramerateInfo::invalidateFrameRate() {
		framerate++;
		frameTime = time->getProgramTime();
		if (lastTimestamp == 0.0) {
			lastTimestamp = frameTime;
			return;
		}
		framerateTimestamp = frameTime;
		if (framerateTimestamp - lastTimestamp >= 1.0) {
			std::cout << framerate << std::endl;
			framerate = 0;
			lastTimestamp = framerateTimestamp;
		}
	}
}
