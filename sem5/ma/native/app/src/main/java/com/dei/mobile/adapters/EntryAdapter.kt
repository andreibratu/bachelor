package com.dei.mobile.adapters

import android.view.LayoutInflater
import android.view.ViewGroup
import androidx.cardview.widget.CardView
import androidx.recyclerview.widget.RecyclerView
import com.dei.mobile.R
import com.dei.mobile.domain.Entry
import com.dei.mobile.services.ColorService
import com.dei.mobile.services.DateService
import com.dei.mobile.services.EntryService
import kotlinx.android.synthetic.main.entry_card_view.view.*
import kotlinx.coroutines.*

class EntryAdapter(private val entryService: EntryService) :
    RecyclerView.Adapter<EntryViewHolder>() {
    var onBind: OnBindCallback? = null

    // Create new views (invoked by the layout manager)
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): EntryViewHolder {
        // Create a new view
        val entryView = LayoutInflater.from(parent.context)
            .inflate(R.layout.entry_card_view, parent, false) as CardView
        return EntryViewHolder(entryView)
    }

    // Replace the contents of a view (invoked by the layout manager)
    override fun onBindViewHolder(holder: EntryViewHolder, position: Int) {
        runBlocking {
            onBind?.onViewBound(holder, position)

            val defer = async(Dispatchers.IO) {
                entryService.getEntries()
            }
            val entries = defer.await()
            val color = entries[position].color
            val contrastColor = ColorService.getContrastingColor(color)

            holder.entryLayout.entry_title.text = entries[position].entryTitle
            holder.entryLayout.entry_date.text = DateService.dateToString(
                entries[position].entryDate
            )
            holder.entryLayout.entry_text.text =
                if (entries[position].entryText.length < 100)
                    entries[position].entryText
                else
                    entries[position].entryText.subSequence(0, 98).toString().plus("...")
            holder.entryLayout.setCardBackgroundColor(color)
            holder.entryLayout.entry_title.setTextColor(contrastColor)
            holder.entryLayout.entry_text.setTextColor(contrastColor)
            holder.entryLayout.entry_date.setTextColor(contrastColor)
        }
    }

    // Return the size of your dataset (invoked by the layout manager)
    override fun getItemCount() = runBlocking {
        val defer = GlobalScope.async(Dispatchers.IO) {
            entryService.getEntries().size
        }
        return@runBlocking defer.await()
    }
}