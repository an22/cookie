//
//  Cookie.h
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#ifndef Cookie_hpp
#define Cookie_hpp

#include "CgAPI.h"
#include <mutex>
#include <thread>
#include <memory>
#include "PlatformSpecificData.hpp"
#include "Shader.hpp"

namespace cookie {

	class Renderer;
	class Scene;

	class Cookie {
	protected:
		static std::unique_ptr<Cookie> instance;
		static std::mutex mutex;

		bool terminate = false;

		std::mutex localMutex;
		std::unique_ptr<PlatformSpecificData> platformData;
		std::unique_ptr<Renderer> renderer;

		explicit Cookie(CgAPI api);
		void loopInternal();
		void clearInternal();
	public:
		static Cookie &getInstance(CgAPI api = CgAPI::OpenGL);

		CgAPI currentAPI;
		Cookie(Cookie &other) = delete;
		Cookie(Cookie &&other) = delete;
		virtual ~Cookie() = default;
		void operator=(const Cookie &) = delete;
		void startRendering();
		void onWindowResized(int32_t width, int32_t height);
		void clear();

		template<class T = PlatformSpecificData>
		T &getPlatformData() const {
			static_assert(
					std::is_base_of<PlatformSpecificData, T>::value,
					"type parameter of this function must derive from cookie::PlatformSpecificData"
			);
			return dynamic_cast<T &>(*platformData);
		}
		void setScene(std::unique_ptr<Scene> scene);
	};
}
#endif /* Cookie_hpp */
