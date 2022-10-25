//
// Created by Michael on 5/26/2022.
//


#include "Cookie.hpp"
#include "Scene.hpp"
#include "CookieFactory.hpp"
#include "DefaultFileManager.hpp"
#include "Macro.h"

int main() {
	try {
		cookie::CookieFactory::init(CgAPI::OpenGL, std::make_unique<cookie::DefaultFileManager>());
		cookie::Cookie &engine = cookie::Cookie::getInstance();
		engine.setScene(std::make_unique<cookie::Scene>());
		engine.startRendering();
	} catch (std::exception &e) {
		LOG_E("%s", e.what());
	}
	return 0;
}