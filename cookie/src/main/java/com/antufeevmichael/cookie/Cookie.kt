package com.antufeevmichael.cookie

import android.content.res.AssetManager
import android.view.Surface

class Cookie {

    /**
     * A native method that is implemented by the 'cookie' native library,
     * which is packaged with this application.
     */
    external fun passControlToNative(surface: Surface, assetManager: AssetManager)

    companion object {
        // Used to load the 'cookie' library on application startup.
        init {
            System.loadLibrary("cookie")
        }
    }
}