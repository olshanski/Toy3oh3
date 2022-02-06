package com.olshanski.toy3oh3.synthesis

class Synthesis {

    /**
     * A native method that is implemented by the 'synthesis' native library,
     * which is packaged with this application.
     */

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

    external fun setQ(q: Double)


    companion object {
        // Used to load the 'synthesis' library on application startup.
        init {
            System.loadLibrary("synthesis")
        }
    }
}