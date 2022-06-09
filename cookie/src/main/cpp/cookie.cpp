#include <jni.h>
#include <android/native_window_jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <EGL/egl.h>
#include <Cookie.hpp>
#include <OpenGLPlatformSpecificData.h>
#include "core.hpp"
#include "CookieFactory.hpp"
#include "platform/android/AndroidFileManager.hpp"
#include "tinygltf/tiny_gltf.h"

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
JNIEXPORT void JNICALL Java_com_antufeevmichael_cookie_Cookie_nativeOnStart(
		JNIEnv *env,
		jobject obj
) {
}
JNIEXPORT void JNICALL Java_com_antufeevmichael_cookie_Cookie_nativeOnResume(
		JNIEnv *env,
		jobject obj
) {

}
JNIEXPORT void JNICALL Java_com_antufeevmichael_cookie_Cookie_nativeOnPause(
		JNIEnv *env,
		jobject obj
) {

}
JNIEXPORT void JNICALL Java_com_antufeevmichael_cookie_Cookie_nativeOnStop(
		JNIEnv *env,
		jobject obj
) {

}
JNIEXPORT void JNICALL Java_com_antufeevmichael_cookie_Cookie_nativeSurfaceDestroyed(
		JNIEnv *env,
		jobject obj
) {
	cookie::Cookie::getInstance().clear();
}
JNIEXPORT void JNICALL Java_com_antufeevmichael_cookie_Cookie_nativeSurfaceCreated(
		JNIEnv *env,
		jobject obj,
		jobject surface
) {
	cookie::Cookie &engine = cookie::Cookie::getInstance();
	engine.getPlatformData<cookie::OpenGLPlatformSpecificData>()
		  .setWindow(static_cast<EGLNativeWindowType>(ANativeWindow_fromSurface(env, surface)));
	engine.startRendering();
}
JNIEXPORT void JNICALL Java_com_antufeevmichael_cookie_Cookie_nativeSurfaceSizeChanged(
		JNIEnv *env,
		jobject obj,
		jint width,
		jint height
) {
	cookie::Cookie::getInstance().onWindowResized(width, height);
}
}