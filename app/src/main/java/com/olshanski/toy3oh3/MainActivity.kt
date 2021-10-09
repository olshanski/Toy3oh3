package com.olshanski.toy3oh3

import android.annotation.SuppressLint
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.MotionEvent
import android.widget.TextView
import com.olshanski.toy3oh3.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    private var doBeep = false

    // TODO: Handle accessibility
    @SuppressLint("ClickableViewAccessibility")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        setupUi()
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

    external fun setTone(note: Int, octave: Int)

    external fun beep(isKeyDown: Boolean)

    private fun setupUi() {
        with(binding) {

            // Example of a call to a native method
            sampleText.text = stringFromJNI()

            buttonBeep.setOnClickListener {
                doBeep = !doBeep

                beep(doBeep)
            }

            buttonTone1.text = getString(R.string.home_label_tone_template, "C3")
            buttonTone2.text = getString(R.string.home_label_tone_template, "A4")

            buttonTone1.setOnClickListener {
                setTone(4, 3)
            }
            buttonTone2.setOnClickListener {
                setTone(1, 4)
            }
        }
    }

    companion object {
        // Used to load the 'toy3oh3' library on application startup.
        init {
            System.loadLibrary("toy3oh3")
        }
    }
}