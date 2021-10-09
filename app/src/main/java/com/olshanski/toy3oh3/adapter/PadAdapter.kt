package com.olshanski.toy3oh3.adapter

import android.view.LayoutInflater
import android.view.ViewGroup
import androidx.recyclerview.widget.RecyclerView
import com.olshanski.toy3oh3.Pad
import com.olshanski.toy3oh3.databinding.ItemPadBinding

class PadAdapter(private val listener: PadClickListener) : RecyclerView.Adapter<PadAdapter.PadViewHolder>() {

    var items: List<Pad> = emptyList()
        set(value) {
            field = value
            notifyDataSetChanged()
        }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): PadViewHolder {
        return PadViewHolder(ItemPadBinding.inflate(LayoutInflater.from(parent.context), null, false))
    }

    override fun onBindViewHolder(holder: PadViewHolder, position: Int) {
        holder.bind(items[position], listener)
    }

    override fun getItemCount(): Int {
        return items.size
    }

    interface PadClickListener {
        fun onPadClicked(note: Int, octave: Int): Unit
    }

    class PadViewHolder(private val binding: ItemPadBinding) : RecyclerView.ViewHolder(binding.root) {

        fun bind(pad: Pad, listener: PadClickListener) {
            binding.textNoteName.text = pad.name
            binding.root.setOnClickListener {
                listener.onPadClicked(pad.note, pad.octave)
            }
        }
    }
}