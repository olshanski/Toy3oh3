package com.olshanski.toy3oh3

import android.annotation.SuppressLint
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.MotionEvent
import android.widget.TextView
import com.olshanski.toy3oh3.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    // TODO: Handle accessibility
    @SuppressLint("ClickableViewAccessibility")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = stringFromJNI()

        binding.buttonBeep.setOnTouchListener { _, motionEvent ->
            return@setOnTouchListener when (motionEvent.action) {
                MotionEvent.ACTION_DOWN -> {
                    beep(true)
                    true
                }

                MotionEvent.ACTION_UP -> {
                    beep(false)
                    true
                }

                else -> false
            }

        }
    }

    override fun onResume() {
        startAudioEngine()
        super.onResume()
    }

    override fun onPause() {
        stopAudioEngine()
        super.onPause()
    }

    /**
     * A native method that is implemented by the 'toy3oh3' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    external fun startAudioEngine()

    external fun stopAudioEngine()

    external fun beep(isKeyDown: Boolean)

    companion object {
        // Used to load the 'toy3oh3' library on application startup.
        init {
            System.loadLibrary("toy3oh3")
        }
    }
}