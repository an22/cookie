//
//  Cookie.h
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#ifndef Cookie_h
#define Cookie_h

#include "CookieFactory.hpp"
#include "CookieConstants.hpp"
#include <memory>

namespace cookie {

    enum class CgAPI {
        OpenGL,
        Vulkan,
        DirectX
    };

    void init(CgAPI api = CgAPI::OpenGL);
    void destroy();

    class Cookie {
    public:

        static CgAPI CURRENT_CG_API;

        std::unique_ptr<PlatformSpecificData> platformData;
        std::unique_ptr<Initializer> initializer;

        explicit Cookie(CgAPI api);

    };

    extern Cookie *engine;

}
#endif /* Cookie_h */
