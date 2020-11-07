package com.dei.mobile.activities

import android.content.Intent
import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.constraintlayout.widget.ConstraintLayout
import androidx.recyclerview.widget.RecyclerView
import com.dei.mobile.BuildConfig
import com.dei.mobile.R
import com.dei.mobile.dagger.DIApplication
import com.dei.mobile.domain.EntryDTO
import com.dei.mobile.services.ColorService
import com.dei.mobile.services.EntryService
import com.dei.mobile.services.NetworkService
import io.ktor.util.*
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking
import javax.inject.Inject

@KtorExperimentalAPI
class EntryDetailsActivity : AppCompatActivity()
{
    @Inject lateinit var entryService: EntryService
    @Inject lateinit var networkService: NetworkService

    override fun onCreate(savedInstanceState: Bundle?)
    {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_entry_details)

        val applicationRef = applicationContext as DIApplication
        applicationRef.dependencyGraph.inject(this)

        val entryDTO = entryService.getCurrentEntry()

        findViewById<TextView>(R.id.entry_title_details).text = entryDTO!!.entryTitle
        findViewById<TextView>(R.id.entry_text_details).text = entryDTO.entryText
        val color = entryDTO.color!!

        findViewById<Button>(R.id.entry_details_edit_button).isEnabled = networkService.isServerUp()
        findViewById<Button>(R.id.entry_details_delete_button).isEnabled = networkService.isServerUp()

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

        if (entryDTO.position != RecyclerView.NO_POSITION)
        {
            findViewById<Button>(R.id.entry_details_delete_button).setOnClickListener {
                runBlocking {
                    val job = launch(Dispatchers.IO) {
                        if (BuildConfig.DEBUG && !networkService.isServerUp()) {
                            error("Assertion failed")
                        }
                        entryDTO.position?.let { it1 -> networkService.deleteEntry(it1) }
                        entryService.deleteEntry(entryDTO.position!!)
                        entryService.setCurrentEntry(
                            EntryDTO(null, null, null, null, null)
                        )
                    }
                    job.join()
                    val intent = Intent(this@EntryDetailsActivity, MainActivity::class.java)
                    intent.putExtra("why", "DELETE")
                    setResult(RESULT_OK, intent)
                    finish()
                }
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
        runBlocking {
            val job = launch(Dispatchers.IO) {
                val entryDTO = entryService.getCurrentEntry()
                val entryToModify = entryService.getEntries()[entryDTO!!.position!!]
                entryToModify.entryText = entryDTO.entryText!!
                entryToModify.entryTitle = entryDTO.entryTitle!!
                entryToModify.color = entryDTO.color!!
            }
            job.join()
            val intent = Intent()
            setResult(RESULT_OK, intent)
            finish()
        }
    }
}