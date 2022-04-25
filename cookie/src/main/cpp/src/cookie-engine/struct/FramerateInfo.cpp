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
		framerateTimestamp = std::chrono::steady_clock::now();
		frameTime = framerateTimestamp;
		lastTimestamp = framerateTimestamp;
	}

	void FramerateInfo::invalidateFrameRate() {
		framerate++;
		frameTime = time->getProgramTime();
		framerateTimestamp = frameTime;
		if (framerateTimestamp - lastTimestamp >= std::chrono::seconds(1)) {
			std::cout << framerate << std::endl;
			framerate = 0;
			lastTimestamp = framerateTimestamp;
		}
	}
}
