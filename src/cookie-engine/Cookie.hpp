//
//  Cookie.h
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#ifndef Cookie_hpp
#define Cookie_hpp

#include "CookieFactory.hpp"
#include "CookieConstants.hpp"
#include <memory>
#include "Scene.hpp"

namespace cookie {

	enum class CgAPI {
		OpenGL,
		Vulkan,
		DirectX
	};

	void init(CgAPI api = CgAPI::OpenGL);
	void setScene(std::shared_ptr<Scene> scene);
	void destroy();

	class Cookie {
	public:
		static CgAPI CURRENT_CG_API;

		std::unique_ptr<PlatformSpecificData> platformData;
		std::unique_ptr<Initializer> initializer;
		std::shared_ptr<Scene> currentScene;

		explicit Cookie(CgAPI api);
	};

	extern Cookie *engine;
	extern Shader *defaultShader;
}
#endif /* Cookie_hpp */
