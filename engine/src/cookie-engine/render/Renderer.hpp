//
// Created by Michael on 10/25/2022.
//

#ifndef COOKIE_ENGINE_RENDERER_HPP
#define COOKIE_ENGINE_RENDERER_HPP

#include <memory>

namespace cookie {
	class Scene;
	class Initializer;
	class PlatformSpecificData;

	class Renderer {
	private:
		std::unique_ptr<Scene> currentScene;
		std::unique_ptr<Initializer> initializer;

	public:
		explicit Renderer(PlatformSpecificData& data);
		virtual ~Renderer();
		bool hasScene();
		void renderFrame();
		void prepare();
		bool isTerminateRequested();
		[[nodiscard]] Scene &getCurrentScene() const;
		void setScene(std::unique_ptr<Scene> scene);
	};
}
#endif //COOKIE_ENGINE_RENDERER_HPP
