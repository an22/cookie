//
//  main.cpp
// cookie-engine
//
//  Created by Antiufieiev Michael on 21.06.2021.
//
#include "Scene.hpp"
#include "Cookie.hpp"
#include <memory>

int main() {
	try {
		cookie::init();
		auto scene = std::make_shared<cookie::Scene>();
		scene->addObject(std::make_shared<cookie::Cube>(0.0f, 0.0f, 0.0f));
		cookie::setScene(scene);
		cookie::engine->currentScene->startLoop();
		cookie::destroy();
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
