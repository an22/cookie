package com.antufeevmichael.cookie

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
    }

    override fun surfaceCreated(holder: SurfaceHolder) {
        cookie.passControlToNative(holder.surface, resources.assets)

    }

    override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) {

    }

    override fun surfaceDestroyed(holder: SurfaceHolder) {

    }

    companion object {
        // Used to load the 'cookie' library on application startup.
        init {
            System.loadLibrary("cookie")
        }
    }
}