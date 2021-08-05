//
//  FramerateInfo.h
//  lighting-test
//
//  Created by Antiufieiev Michael on 01.07.2021.
//

#ifndef FramerateInfo_hpp
#define FramerateInfo_hpp

#include <GLFW/glfw3.h>
#include <iostream>
#include "Time.h"

namespace cookie {

class FramerateInfo {
private:
	Time* time; // TODO provide time instance
	double lastTimestamp = 0.0;
	
public:
	uint8_t framerate = 0;
	double framerateTimestamp = 0.0;
	double frameTime = 0.0;
	
	void invalidateFrameRate() {
		framerate++;
		frameTime = time->getProgramTime();
		if(lastTimestamp == 0.0) {
			lastTimestamp = frameTime;
			return;
		}
		framerateTimestamp = frameTime;
		if(framerateTimestamp - lastTimestamp >= 1.0) {
			std::cout << framerate << std::endl;
			framerate = 0;
			lastTimestamp = framerateTimestamp;
		}
	}
};
}

#endif /* FramerateInfo_h */
