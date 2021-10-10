package com.olshanski.toy3oh3.adapter

import android.annotation.SuppressLint
import android.view.LayoutInflater
import android.view.MotionEvent
import android.view.ViewGroup
import androidx.recyclerview.widget.RecyclerView
import com.olshanski.toy3oh3.Pad
import com.olshanski.toy3oh3.databinding.ItemPadBinding

class PadAdapter(private val listener: KeyListener) :
    RecyclerView.Adapter<PadAdapter.PadViewHolder>() {

    var items: List<Pad> = emptyList()
        set(value) {
            field = value
            notifyDataSetChanged()
        }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): PadViewHolder {
        return PadViewHolder(
            ItemPadBinding.inflate(
                LayoutInflater.from(parent.context),
                null,
                false
            )
        )
    }

    override fun onBindViewHolder(holder: PadViewHolder, position: Int) {
        holder.bind(items[position], listener)
    }

    override fun getItemCount(): Int {
        return items.size
    }

    interface KeyListener {

        fun onKeyPressed(note: Int, octave: Int)

        fun onKeyReleased(note: Int, octave: Int)
    }

    class PadViewHolder(private val binding: ItemPadBinding) :
        RecyclerView.ViewHolder(binding.root) {

        @SuppressLint("ClickableViewAccessibility")
        fun bind(pad: Pad, listener: KeyListener) {
            binding.textNoteName.text = pad.name
            binding.root.setOnTouchListener { view, motionEvent ->
                return@setOnTouchListener when (motionEvent.action) {
                    MotionEvent.ACTION_DOWN -> {
                        listener.onKeyPressed(pad.note, pad.octave)
                        true
                    }

                    MotionEvent.ACTION_UP, MotionEvent.ACTION_CANCEL -> {
                        listener.onKeyReleased(pad.note, pad.octave)
                        true
                    }

                    else -> false
                }
            }
        }
    }
}