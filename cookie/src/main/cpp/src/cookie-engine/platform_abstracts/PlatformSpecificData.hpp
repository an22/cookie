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
		virtual int32_t width() { return _width; };
		virtual int32_t height()  { return _height; };
		virtual void setWidth(int32_t width) { _width = width; };
		virtual void setHeight(int32_t height)  { _height = height; };
		virtual ~PlatformSpecificData() = default;
	};
}

#endif /* PlatformSpecificData_hpp */
