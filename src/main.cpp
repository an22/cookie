//
//  main.cpp
// cookie-engine
//
//  Created by Antiufieiev Michael on 21.06.2021.
//
#include <iostream>
#include "Cookie.hpp"
#include "Cube.hpp"

int main() {
	try {
		cookie::Cookie& engine = cookie::Cookie::getInstance(CgAPI::OpenGL);
		auto scene = std::make_shared<cookie::Scene>();
		engine.setScene(scene);
		scene->addObject(std::make_shared<cookie::Cube>(0.0f, 0.0f, 0.0f));
		engine.currentScene->startLoop();
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
