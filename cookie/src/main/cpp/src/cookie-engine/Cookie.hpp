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
#include <thread>
#include "PlatformSpecificData.hpp"
#include "Initializer.hpp"
#include "Shader.hpp"
#include "Scene.hpp"

namespace cookie {

	class Cookie {
	private:
		static std::unique_ptr<Cookie> instance;
		static std::mutex mutex;

		bool terminate = false;

		std::mutex localMutex;
		std::thread* renderingLoop;
		std::unique_ptr<PlatformSpecificData> platformData;
		std::unique_ptr<Initializer> initializer;
		std::unique_ptr<Scene> currentScene;
		std::unique_ptr<Shader> currentShader;

		explicit Cookie(CgAPI api);
		void loopInternal();
	public:
		CgAPI currentAPI;
		Cookie(Cookie &other) = delete;
		Cookie(Cookie &&other) = delete;
		virtual ~Cookie() = default;
		void operator=(const Cookie &) = delete;
		void prepareRendering();
		void startRendering();
		void clear();

		template<class T = PlatformSpecificData>
		T &getPlatformData() const {
			static_assert(
					std::is_base_of<PlatformSpecificData, T>::value,
					"type parameter of this function must derive from cookie::PlatformSpecificData"
			);
			return dynamic_cast<T &>(*platformData);
		}
		template<class T = Shader>
		T &getCurrentShader() const {
			static_assert(
					std::is_base_of<Shader, T>::value,
					"type parameter of this function must derive from cookie::Shader"
			);
			return dynamic_cast<T &>(*currentShader);
		}

		Scene &getCurrentScene() const;
		void setScene(std::unique_ptr<Scene> scene);
		static Cookie &getInstance(CgAPI api = CgAPI::OpenGL);
	};
}
#endif /* Cookie_hpp */