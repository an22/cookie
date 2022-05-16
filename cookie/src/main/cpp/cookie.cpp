#include <jni.h>
#include <android/native_window_jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <EGL/egl.h>
#include "core.hpp"
#include "CookieFactory.hpp"
#include "AndroidFileManager.hpp"
#include "tiny_gltf.h"

extern "C" JNIEXPORT
void JNICALL Java_com_antufeevmichael_cookie_Cookie_passControlToNative(
		JNIEnv *env,
		jobject /* this */,
		jobject surface,
		jobject assetManager
) {
	auto* aManager = AAssetManager_fromJava(env, assetManager);
	std::unique_ptr<cookie::FileManager> fileManager(new cookie::AndroidFileManager(aManager));
    cookie::CookieFactory::init(
            CgAPI::OpenGL,
            std::move(fileManager)
    );
    start(static_cast<EGLNativeWindowType>(ANativeWindow_fromSurface(env, surface)));
}