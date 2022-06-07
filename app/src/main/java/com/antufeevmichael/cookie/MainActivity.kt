package com.antufeevmichael.cookie

import android.graphics.PixelFormat
import android.os.Bundle
import android.view.SurfaceHolder
import androidx.appcompat.app.AppCompatActivity
import com.antufeevmichael.cookie.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity(), SurfaceHolder.Callback {

    private lateinit var binding: ActivityMainBinding
    private val cookie = Cookie()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.holder.addCallback(this)
        binding.sampleText.holder.setFormat(PixelFormat.RGBA_8888)
        cookie.nativeOnCreate(resources.assets)
    }

    override fun surfaceCreated(holder: SurfaceHolder) {
        cookie.nativeSurfaceCreated(holder.surface)
    }

    override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) {
        cookie.nativeSurfaceSizeChanged(width, height)
    }

    override fun surfaceDestroyed(holder: SurfaceHolder) {
        cookie.nativeSurfaceDestroyed()
    }

    override fun onStart() {
        cookie.nativeOnStart()
        super.onStart()
    }

    override fun onResume() {
        cookie.nativeOnResume()
        super.onResume()
    }

    override fun onPause() {
        super.onPause()
        cookie.nativeOnPause()
    }

    override fun onStop() {
        super.onStop()
        cookie.nativeOnStop()
    }

    companion object {
        // Used to load the 'cookie' library on application startup.
        init {
            System.loadLibrary("cookie")
        }
    }
}