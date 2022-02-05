package com.olshanski.toy3oh3

import android.annotation.SuppressLint
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.SeekBar
import androidx.recyclerview.widget.GridLayoutManager
import com.olshanski.toy3oh3.adapter.PadAdapter
import com.olshanski.toy3oh3.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

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

    external fun playNote(note: Int, octave: Int)

    external fun releaseNote()

    external fun setVolume(volume: Double)

    external fun setAttack(attackMillis: Int)

    external fun setDecay(decayMillis: Int)

    external fun setRelease(releaseMillis: Int)

    external fun setSustain(sustain: Double)

    external fun setWaveform(waveform: Int)

    external fun setCutoffFrequency(frequencyHz: Int)

    private fun setupUi() {
        with(binding) {


            val lM = GridLayoutManager(this@MainActivity, 4, GridLayoutManager.VERTICAL, false)
            val adapter = PadAdapter(listener = object : PadAdapter.KeyListener {

                private var currentPad: Pair<Int, Int>? = null

                override fun onKeyPressed(note: Int, octave: Int) {
                    currentPad = note to octave
                    playNote(note, octave)

                }

                override fun onKeyReleased(note: Int, octave: Int) {
                    if (note == currentPad?.first && octave == currentPad?.second) {
                        releaseNote()
                    }
                }
            })

            pads.layoutManager = lM
            pads.adapter = adapter

            adapter.items = NOTES

            val seekBarChangeListener = object : SeekBar.OnSeekBarChangeListener {
                override fun onProgressChanged(
                    seekBar: SeekBar?,
                    progress: Int,
                    fromUser: Boolean
                ) {
                    seekBar ?: return

                    when (seekBar) {
                        attackSeekbar -> {
                            attackValue.text = progress.toString()
                            setAttack(progress)
                        }

                        decaySeekbar -> {
                            decayValue.text = progress.toString()
                            setDecay(progress)
                        }

                        releaseSeekbar -> {
                            releaseValue.text = progress.toString()
                            setRelease(progress)
                        }

                        sustainSeekbar -> {
                            val level = progress / 100.0
                            sustainValue.text = level.toString()
                            setSustain(level)
                        }

                        cutoffSeekbar -> {
                            cutoffValue.text = progress.toString()
                            setCutoffFrequency(progress)
                        }
                    }
                }

                override fun onStartTrackingTouch(seekBar: SeekBar?) {
                    // no op
                }

                override fun onStopTrackingTouch(seekBar: SeekBar?) {
                    // no op
                }

            }

            attackSeekbar.setOnSeekBarChangeListener(seekBarChangeListener)
            decaySeekbar.setOnSeekBarChangeListener(seekBarChangeListener)
            releaseSeekbar.setOnSeekBarChangeListener(seekBarChangeListener)
            sustainSeekbar.setOnSeekBarChangeListener(seekBarChangeListener)
            cutoffSeekbar.setOnSeekBarChangeListener(seekBarChangeListener)

            attackSeekbar.progress = 500
            decaySeekbar.progress = 500
            releaseSeekbar.progress = 500
            sustainSeekbar.progress = 20
            cutoffSeekbar.progress = 22000

            waveformSelector.setOnClickListener {
                var ordinal = when (waveform) {
                    Waveform.SINE -> 0
                    else -> waveform.ordinal + 1
                }

                waveform = Waveform.values()[ordinal]

                waveformSelector.drawable.level = ordinal

                setWaveform(ordinal)
            }
        }
    }

    private var waveform = Waveform.SAWTOOTH

    enum class Waveform {
        SAWTOOTH, PULSE, SINE
    }

    private companion object {
        // Used to load the 'toy3oh3' library on application startup.
        init {
            System.loadLibrary("toy3oh3")
        }

        private val NOTES = listOf(
            Pad(4, 1, "C"),
            Pad(5, 1, "C#"),
            Pad(6, 1, "D"),
            Pad(7, 1, "D#"),
            Pad(8, 1, "E"),
            Pad(9, 1, "F"),
            Pad(10, 1, "F#"),
            Pad(11, 1, "G"),
            Pad(12, 1, "G#"),
            Pad(1, 2, "A"),
            Pad(2, 2, "B#"),
            Pad(3, 2, "B"),
        )
    }
}