  package com.dei.mobile.repositories

import com.dei.mobile.domain.Entry
import com.dei.mobile.repositories.database.AppDatabase
import javax.inject.Singleton

  @Singleton
class DatabaseRepository constructor(private val appDatabase: AppDatabase) : Repository
{
    override suspend fun getEntries(): MutableList<Entry>
    {
        return appDatabase.entityDao().getAll().toMutableList()
    }

    override suspend fun addEntry(entry: Entry): Long
    {
        return appDatabase.entityDao().insertAll(entry)[0]
    }

    override suspend fun deleteEntry(idx: Int)
    {
        val entryToDelete = appDatabase.entityDao().getAll()[idx]
        appDatabase.entityDao().delete(entryToDelete)
    }

    override suspend fun editEntry(idx: Int, editedEntry: Entry)
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