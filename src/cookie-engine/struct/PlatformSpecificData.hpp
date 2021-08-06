//
//  PlatformSpecificData.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 03.08.2021.
//

#ifndef PlatformSpecificData_hpp
#define PlatformSpecificData_hpp

#include <cstdint>

namespace cookie {

class PlatformSpecificData {
protected:
	int32_t _width = 0;
	int32_t _height = 0;
public:
	
	virtual int32_t width() = 0;
	virtual int32_t height() = 0;
	virtual ~PlatformSpecificData() = default;
};
}

#endif /* PlatformSpecificData_hpp */
