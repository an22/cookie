//
//  main.cpp
// cookie-engine
//
//  Created by Antiufieiev Michael on 21.06.2021.
//
#include "Scene.hpp"
#include "Cookie.hpp"

int main() {
    try {
        cookie::init();
        cookie::Scene scene;
        scene.startLoop();
        cookie::destroy();
    }catch (std::exception& e) {

    }
    return 0;
}
