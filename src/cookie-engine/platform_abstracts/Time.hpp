//
//  Time.h
//  cookie-engine
//
//  Created by Antiufieiev Michael on 04.08.2021.
//

#ifndef Time_hpp
#define Time_hpp

namespace cookie {

	class Time {

	public:
		Time() = default;
		virtual ~Time() = default;
		virtual double getProgramTime() = 0;
		virtual double getFrameTime() = 0;
	};
}
#endif /* Time_hpp */
