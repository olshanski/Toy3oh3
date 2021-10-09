package com.olshanski.toy3oh3

import android.annotation.SuppressLint
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import androidx.recyclerview.widget.GridLayoutManager
import com.olshanski.toy3oh3.adapter.PadAdapter
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

            val lM = GridLayoutManager(this@MainActivity, 6, GridLayoutManager.VERTICAL, false)
            val adapter = PadAdapter(listener = object : PadAdapter.PadClickListener {
                override fun onPadClicked(note: Int, octave: Int) {
                    setTone(note, octave)
                }
            })

            pads.layoutManager = lM
            pads.adapter = adapter

            adapter.items = NOTES
        }
    }

    private companion object {
        // Used to load the 'toy3oh3' library on application startup.
        init {
            System.loadLibrary("toy3oh3")
        }

        private val NOTES = listOf(
            Pad(4, 3, "C"),
            Pad(5, 3, "C#"),
            Pad(6, 3, "D"),
            Pad(7, 3, "D#"),
            Pad(8, 3, "E"),
            Pad(9, 3, "F"),
            Pad(10, 3, "F#"),
            Pad(11, 3, "G"),
            Pad(12, 3, "G#"),
            Pad(1, 4, "A"),
            Pad(2, 4, "A#"),
            Pad(3, 4, "B"),
        )
    }
}