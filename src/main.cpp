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
		cookie::setScene(std::make_unique<cookie::Scene>());
		cookie::engine->currentScene->startLoop();
		cookie::destroy();
	} catch (std::exception &e) {
	}
	return 0;
}
