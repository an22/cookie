//
//  Constants.cpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#include <stdio.h>
#include "Constants.h"
#include "Cookie.h"

namespace cookie {

void init(CgAPI api) {// TODO change to Vulkan
	engine = new Cookie(api);
}

void destroy() {
	delete engine;
}

}
