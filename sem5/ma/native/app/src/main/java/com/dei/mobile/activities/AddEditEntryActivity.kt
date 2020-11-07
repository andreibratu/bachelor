package com.dei.mobile.activities

import android.content.Intent
import android.os.Bundle
import android.widget.EditText
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.constraintlayout.widget.ConstraintLayout
import com.dei.mobile.BuildConfig
import com.dei.mobile.R
import com.dei.mobile.dagger.DIApplication
import com.dei.mobile.domain.Entry
import com.dei.mobile.services.ColorService
import com.dei.mobile.services.EntryService
import com.dei.mobile.services.NetworkService
import com.madrapps.pikolo.ColorPicker
import com.madrapps.pikolo.listeners.SimpleColorSelectionListener
import io.ktor.util.*
import kotlinx.coroutines.*
import java.util.*
import javax.inject.Inject
import kotlin.coroutines.CoroutineContext


@KtorExperimentalAPI
class AddEditEntryActivity : AppCompatActivity(), CoroutineScope
{
    @Inject lateinit var entryService: EntryService
    @Inject lateinit var networkService: NetworkService
    private lateinit var job: Job
    override val coroutineContext: CoroutineContext
        get() = job + Dispatchers.Main

    override fun onCreate(savedInstanceState: Bundle?)
    {
        super.onCreate(savedInstanceState)
        job = Job()
        setContentView(R.layout.activity_add_edit_entry)

        val applicationRef = applicationContext as DIApplication
        applicationRef.dependencyGraph.inject(this)

        val isCreate = entryService.isCreate

        val layoutTitle = findViewById<TextView>(R.id.add_edit_screen_title)
        val entryTitle = findViewById<EditText>(R.id.add_edit_title_input)
        val submitButton = findViewById<TextView>(R.id.submit_button)
        val entryText = findViewById<EditText>(R.id.add_edit_text_input)
        val background = findViewById<ConstraintLayout>(R.id.add_edit_screen_layout)
        val colorPicker = findViewById<ColorPicker>(R.id.entry_color_picker)
        var currentColor = 0

        if (!isCreate)
        {
            entryTitle.setText(
                entryService.getCurrentEntry()!!.entryTitle,
                TextView.BufferType.EDITABLE
            )
            entryText.setText(
                entryService.getCurrentEntry()!!.entryText,
                TextView.BufferType.EDITABLE
            )
        }

        layoutTitle.text = if (isCreate) "Add entry" else "Edit entry"
        submitButton.text = if (isCreate) "Create" else "Edit"

        entryService.getCurrentEntry()!!.color?.let { colorPicker.setColor(it) }

        colorPicker.setColorSelectionListener(object :
            SimpleColorSelectionListener() {
            override fun onColorSelected(color: Int)
            {
                val contrastColor = ColorService.getContrastingColor(color)
                background.setBackgroundColor(color)
                entryTitle.setTextColor(contrastColor)
                submitButton.setTextColor(contrastColor)
                submitButton.setBackgroundColor(color)
                entryTitle.setTextColor(contrastColor)
                entryTitle.setHintTextColor(contrastColor)
                entryText.setHintTextColor(contrastColor)
                entryText.setTextColor(contrastColor)
                layoutTitle.setTextColor(contrastColor)
                currentColor = color
            }
        })

        submitButton.setOnClickListener {
            runBlocking {
                job = launch(Dispatchers.IO){
                    val currEntry = entryService.getCurrentEntry()!!
                    currEntry.entryTitle = entryTitle.text.toString()
                    currEntry.entryText = entryText.text.toString()
                    currEntry.color = currentColor
                    currEntry.entryDate = Calendar.getInstance()
                    val id = entryService.submitEntry(currEntry)
                    if (entryService.isCreate)
                    {
                        if(networkService.isServerUp())
                        {
                            networkService.postEntry(Entry(
                                uid = id.toInt(),
                                entryText = currEntry.entryText!!,
                                entryTitle = currEntry.entryTitle!!,
                                entryDate = currEntry.entryDate!!,
                                color = currEntry.color!!
                            ))
                        }
                    }
                    else
                    {
                        if (BuildConfig.DEBUG && !networkService.isServerUp()) {
                            error("Assertion failed")
                        }
                        networkService.updateEntry(Entry(
                            uid = id.toInt(),
                            entryText = currEntry.entryText!!,
                            entryTitle = currEntry.entryTitle!!,
                            entryDate = currEntry.entryDate!!,
                            color = currEntry.color!!
                        ))
                    }
                }
                job.join()
                val intent = Intent()
                setResult(RESULT_OK, intent)
                finish()
            }
        }
    }

    override fun onDestroy() {
        super.onDestroy()
        job.cancel()
    }
}