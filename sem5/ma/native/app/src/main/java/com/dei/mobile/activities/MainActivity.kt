package com.dei.mobile.activities

import android.content.Intent
import android.os.Bundle
import android.view.View.INVISIBLE
import android.view.View.VISIBLE
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.cardview.widget.CardView
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.dei.mobile.R
import com.dei.mobile.adapters.EntryAdapter
import com.dei.mobile.adapters.EntryViewHolder
import com.dei.mobile.adapters.OnBindCallback
import com.dei.mobile.dagger.DIApplication
import com.dei.mobile.domain.EntryDTO
import com.dei.mobile.services.EntryService
import com.google.android.material.floatingactionbutton.FloatingActionButton
import kotlinx.android.synthetic.main.entry_card_view.view.*
import javax.inject.Inject

class MainActivity : AppCompatActivity()
{
    private lateinit var recyclerView: RecyclerView
    private lateinit var viewAdapter: EntryAdapter
    private lateinit var viewManager: RecyclerView.LayoutManager
    @Inject lateinit var entryService: EntryService

    override fun onCreate(savedInstanceState: Bundle?)
    {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val applicationRef = applicationContext as DIApplication
        applicationRef.dependencyGraph.inject(this)

        viewManager = LinearLayoutManager(this)
        viewAdapter = EntryAdapter(entryService)
        viewAdapter.onBind = object : OnBindCallback {
            override fun onViewBound(viewHolder: EntryViewHolder?, position: Int) {
                viewHolder?.itemView?.setOnClickListener {
                    // Get card color
                    val layout = findViewById<CardView>(R.id.entry_card_layout)
                    val cardColor = layout.cardBackgroundColor.defaultColor

                    val intent = Intent(applicationContext, EntryDetailsActivity::class.java)
                    entryService.setCurrentEntry(
                        EntryDTO(
                            viewHolder.itemView.entry_title.text as String,
                            viewHolder.itemView.entry_text.text as String,
                            cardColor,
                            position,
                            null
                        )
                    )
                    this@MainActivity.startActivityForResult(intent, 1)
                }
            }
        }

        recyclerView = findViewById<RecyclerView>(R.id.entry_recycler_view).apply {
            // use this setting to improve performance if you know that changes
            // in content do not change the layout size of the RecyclerView
            setHasFixedSize(true)
            // use a linear layout manager
            layoutManager = viewManager
            // specify an viewAdapter (see also next example)
            adapter = viewAdapter
        }

        findViewById<FloatingActionButton>(R.id.add_entry_fab).setOnClickListener {
            val intent = Intent(this, AddEditEntryActivity::class.java)
            entryService.isCreate = true
            startActivityForResult(intent, 2)
        }
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?)
    {
        super.onActivityResult(requestCode, resultCode, data)
        viewAdapter.notifyDataSetChanged()
        findViewById<TextView>(R.id.empty_list_text).visibility =
            if(viewAdapter.itemCount == 0) VISIBLE else INVISIBLE
    }
}
