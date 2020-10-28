  package com.dei.mobile.repositories

import com.dei.mobile.domain.Entry
import com.dei.mobile.repositories.database.AppDatabase
import javax.inject.Inject
import javax.inject.Singleton

@Singleton
class DatabaseRepository constructor(private val appDatabase: AppDatabase) : Repository
{
    override fun getEntries(): MutableList<Entry>
    {
        return appDatabase.entityDao().getAll().toMutableList()
    }

    override fun addEntry(entry: Entry)
    {
        appDatabase.entityDao().insertAll(entry)
    }

    override fun deleteEntry(idx: Int)
    {
        val entryToDelete = appDatabase.entityDao().getAll()[idx]
        appDatabase.entityDao().delete(entryToDelete)
    }

    override fun editEntry(idx: Int, editedEntry: Entry)
    {
        val id = appDatabase.entityDao().getAll()[idx].uid!!
        appDatabase.entityDao().update(
            id = id,
            entry_title = editedEntry.entryTitle,
            entry_text = editedEntry.entryText,
            color_mask = editedEntry.color
        )
    }
}