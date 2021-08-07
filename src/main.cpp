//
//  main.cpp
// cookie-engine
//
//  Created by Antiufieiev Michael on 21.06.2021.
//
#include "Scene.hpp"
#include "Cookie.hpp"

int main(int argc, const char * argv[]) {
	cookie::init();
	cookie::Scene scene;
	scene.init();
	scene.startLoop();
	return 0;
}
