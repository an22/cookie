//
//  FramerateInfo.h
//  cookie-engine
//
//  Created by Antiufieiev Michael on 01.07.2021.
//

#ifndef FramerateInfo_hpp
#define FramerateInfo_hpp

#include <memory>
#include <chrono>
#include "platform_abstracts/Time.hpp"

namespace cookie {

	class FramerateInfo {
	private:
		std::unique_ptr<Time> time;

	public:
		unsigned int framerate;
		std::chrono::steady_clock::time_point framerateTimestamp;
		std::chrono::steady_clock::time_point frameTime;
		std::chrono::steady_clock::time_point lastTimestamp;

		FramerateInfo();
		void invalidateFrameRate();
	};
}

#endif /* FramerateInfo_hpp */
