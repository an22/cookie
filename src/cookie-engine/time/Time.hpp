//
//  Time.h
//  cookie-engine
//
//  Created by Antiufieiev Michael on 04.08.2021.
//

#ifndef Time_h
#define Time_h

namespace cookie {

class Time{
	
	
public:
	
	Time() {}
	virtual ~Time() {}
	virtual double getProgramTime() = 0;
	virtual double getFrameTime() = 0;
};
}
#endif /* Time_h */