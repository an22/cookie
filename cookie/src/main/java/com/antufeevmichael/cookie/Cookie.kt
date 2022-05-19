package com.antufeevmichael.cookie

import android.content.res.AssetManager
import android.view.Surface

class Cookie {

    /**
     * A native method that is implemented by the 'cookie' native library,
     * which is packaged with this application.
     */
    external fun nativeOnCreate(assetManager: AssetManager)
    external fun nativeOnStart()
    external fun nativeOnResume()
    external fun nativeOnPause()
    external fun nativeOnStop()
    external fun nativeClearSurface()
    external fun nativeSetSurface(surface: Surface)

    companion object {
        // Used to load the 'cookie' library on application startup.
        init {
            System.loadLibrary("cookie")
        }
    }
}