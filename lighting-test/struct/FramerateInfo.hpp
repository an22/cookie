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
#endif /* FramerateInfo_h */

class FramerateInfo {
private:
	double lastTimestamp = 0.0;
	
public:
	ushort framerate = 0;
	double framerateTimestamp = 0.0;
	
	void invalidateFrameRate() {
		framerate++;
		if(lastTimestamp == 0.0) {
			lastTimestamp = glfwGetTime();
			return;
		}
		framerateTimestamp = glfwGetTime();
		if(framerateTimestamp - lastTimestamp >= 1.0) {
			std::cout << framerate << std::endl;
			framerate = 0;
			lastTimestamp = framerateTimestamp;
		}
	}
};
