#include "Cookie.hpp"
#include "CookieFactory.hpp"
#include "DefaultFileManager.hpp"
#include "Macro.h"
#include "com_antiufieievmichael_NativeBridge.h"

JNIEXPORT void JNICALL Java_com_antiufieievmichael_NativeBridge_example(JNIEnv *env, jobject obj)
{
	try {
		cookie::CookieFactory::init(CgAPI::OpenGL, std::make_unique<cookie::DefaultFileManager>());
		cookie::Cookie& engine = cookie::Cookie::getInstance();
		engine.startRendering();
	} catch (std::exception &e) {
		LOG_E(e.what());
	}
}