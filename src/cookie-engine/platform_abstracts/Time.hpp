//
//  Time.h
//  cookie-engine
//
//  Created by Antiufieiev Michael on 04.08.2021.
//

#ifndef Time_hpp
#define Time_hpp

#include <chrono>

namespace cookie {

	class Time {

	public:
		Time() = default;
		virtual ~Time() = default;
		std::chrono::steady_clock::time_point getProgramTime();
		virtual double getFrameTime() = 0;
	};
}
#endif /* Time_hpp */
