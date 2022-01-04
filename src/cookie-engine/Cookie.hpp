//
//  Cookie.h
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#ifndef Cookie_hpp
#define Cookie_hpp

#include <CgAPI.h>
#include <memory>
#include <mutex>
#include "PlatformSpecificData.hpp"
#include "Initializer.hpp"
#include "Shader.hpp"
#include "Scene.hpp"

namespace cookie {

	class Cookie {
	private:
		static std::unique_ptr<Cookie> instance;
		static std::mutex mutex;

		explicit Cookie(CgAPI api);
	public:

		std::unique_ptr<PlatformSpecificData> platformData;
		std::unique_ptr<Initializer> initializer;
		std::shared_ptr<Scene> currentScene;
		std::unique_ptr<Shader> defaultShader;
		CgAPI currentAPI;

		Cookie(Cookie &other) = delete;
		Cookie(Cookie &&other) = delete;
		void operator=(const Cookie &) = delete;
		~Cookie();

		void setScene(std::shared_ptr<Scene> scene);
		static Cookie& getInstance(CgAPI api = CgAPI::OpenGL);
	};
}
#endif /* Cookie_hpp */
