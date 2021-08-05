//
//  Constants.h
//  cookie-engine
//
//  Created by Antiufieiev Michael on 03.08.2021.
//

#ifndef Constants_h
#define Constants_h

namespace cookie {

enum class CgAPI {
	OpenGL,
	Vulkan,
	DirectX
};

void init(CgAPI api = CgAPI::OpenGL);

void destroy();

}

#endif /* Constants_h */
