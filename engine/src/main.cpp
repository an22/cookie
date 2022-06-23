//
// Created by Michael on 5/26/2022.
//


#include "Cookie.hpp"
#include "CookieFactory.hpp"
#include "DefaultFileManager.hpp"
#include "Macro.h"

int main() {
	try {
		cookie::CookieFactory::init(CgAPI::OpenGL, std::make_unique<cookie::DefaultFileManager>());
		cookie::Cookie& engine = cookie::Cookie::getInstance();
		engine.startRendering();
	} catch (std::exception &e) {
		LOG_E(e.what());
	}
	return 0;
}