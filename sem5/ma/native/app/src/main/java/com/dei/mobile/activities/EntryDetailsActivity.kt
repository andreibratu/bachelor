package com.dei.mobile.activities

import android.content.Intent
import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.constraintlayout.widget.ConstraintLayout
import androidx.recyclerview.widget.RecyclerView
import com.dei.mobile.dagger.DIApplication
import com.dei.mobile.R
import com.dei.mobile.domain.EntryDTO
import com.dei.mobile.services.ColorService
import com.dei.mobile.services.EntryService
import javax.inject.Inject

class EntryDetailsActivity : AppCompatActivity()
{
    @Inject lateinit var entryService: EntryService

    override fun onCreate(savedInstanceState: Bundle?)
    {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_entry_details)

        val applicationRef = applicationContext as DIApplication
        applicationRef.dependencyGraph.inject(this)

        val entry = entryService.getCurrentEntry()

        findViewById<TextView>(R.id.entry_title_details).text = entry!!.entryTitle
        findViewById<TextView>(R.id.entry_text_details).text = entry.entryText
        val color = entry.color!!

        findViewById<Button>(R.id.entry_details_delete_button).setBackgroundColor(color)
        findViewById<Button>(R.id.entry_details_edit_button).setBackgroundColor(color)
        findViewById<Button>(R.id.entry_details_delete_button).setTextColor(
            ColorService.getContrastingColor(color)
        )
        findViewById<Button>(R.id.entry_details_edit_button).setBackgroundColor(color)
        findViewById<Button>(R.id.entry_details_edit_button).setTextColor(
            ColorService.getContrastingColor(color)
        )

        findViewById<ConstraintLayout>(R.id.entry_details_layout).setBackgroundColor(color)

        if (entry.position != RecyclerView.NO_POSITION)
        {
            findViewById<Button>(R.id.entry_details_delete_button).setOnClickListener {
                entryService.deleteEntry(entry.position!!)
                entryService.setCurrentEntry(
                    EntryDTO(null, null, null, null, null)
                )
                val intent = Intent(this@EntryDetailsActivity, MainActivity::class.java)
                intent.putExtra("why", "DELETE")
                setResult(RESULT_OK, intent)
                finish()
            }

            findViewById<Button>(R.id.entry_details_edit_button).setOnClickListener {
                entryService.isCreate = false
                val intent = Intent(this, AddEditEntryActivity::class.java)
                startActivityForResult(intent, 3)
            }
        }
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?)
    {
        super.onActivityResult(requestCode, resultCode, data)
        val entryDTO = entryService.getCurrentEntry()
        val entryToModify = entryService.entries[entryDTO!!.position!!]
        entryToModify.entryText = entryDTO.entryText!!
        entryToModify.entryTitle = entryDTO.entryTitle!!
        entryToModify.color = entryDTO.color!!
        val intent = Intent()
        setResult(RESULT_OK, intent)
        finish()
    }
}