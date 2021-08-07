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
#include "Time.hpp"

namespace cookie {

class FramerateInfo {
private:
	std::unique_ptr<Time> time;
	double lastTimestamp;
	
public:
	uint32_t framerate;
	double framerateTimestamp;
	double frameTime;
	
	FramerateInfo();
	
	void invalidateFrameRate();
};
}

#endif /* FramerateInfo_h */
