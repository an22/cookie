#include <jni.h>
#include <android/native_window_jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <EGL/egl.h>
#include <Cookie.hpp>
#include <OpenGLPlatformSpecificData.h>
#include "core.hpp"
#include "CookieFactory.hpp"
#include "AndroidFileManager.hpp"
#include "tiny_gltf.h"

extern "C" {
JNIEXPORT void JNICALL Java_com_antufeevmichael_cookie_Cookie_nativeOnCreate(
		JNIEnv *env,
		jobject obj,
		jobject assetManager
) {
	auto *aManager = AAssetManager_fromJava(env, assetManager);
	std::unique_ptr<cookie::FileManager> fileManager(new cookie::AndroidFileManager(aManager));
	cookie::CookieFactory::init(
			CgAPI::OpenGL,
			std::move(fileManager)
	);
}
JNIEXPORT void JNICALL Java_com_antufeevmichael_cookie_Cookie_nativeOnStart(JNIEnv *env, jobject obj) {
}
JNIEXPORT void JNICALL Java_com_antufeevmichael_cookie_Cookie_nativeOnResume(JNIEnv *env, jobject obj) {

}
JNIEXPORT void JNICALL Java_com_antufeevmichael_cookie_Cookie_nativeOnPause(JNIEnv *env, jobject obj) {

}
JNIEXPORT void JNICALL Java_com_antufeevmichael_cookie_Cookie_nativeOnStop(JNIEnv *env, jobject obj) {

}
JNIEXPORT void JNICALL Java_com_antufeevmichael_cookie_Cookie_nativeClearSurface(JNIEnv *env, jobject obj) {
	cookie::Cookie &engine = cookie::Cookie::getInstance();
	engine.clear();
}
JNIEXPORT void JNICALL Java_com_antufeevmichael_cookie_Cookie_nativeSetSurface(
		JNIEnv *env,
		jobject obj,
		jobject surface
) {
	cookie::Cookie &engine = cookie::Cookie::getInstance();
	auto &data = engine.getPlatformData<OpenGLPlatformSpecificData>();
	data.setWindow(static_cast<EGLNativeWindowType>(ANativeWindow_fromSurface(env, surface)));
	engine.startRendering();
}
}