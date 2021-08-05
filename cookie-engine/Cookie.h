//
//  Cookie.h
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#ifndef Cookie_h
#define Cookie_h
#include "CookieFactory.h"
#include "Constants.h"
#include <memory>

namespace cookie {

class Cookie {
public:
	
	static CgAPI CURRENT_CG_API;
	
	std::unique_ptr<PlatformSpecificData> platformData;
	std::unique_ptr<Initializer> initializer;

	Cookie(CgAPI api);
	
};

extern Cookie* engine;

}
#endif /* Cookie_h */
