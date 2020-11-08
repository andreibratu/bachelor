package com.dei.mobile.repositories

import com.dei.mobile.domain.Entry
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.withContext
import javax.inject.Singleton

@Singleton
class InMemoryRepository constructor(private val entries: MutableList<Entry>) : Repository
{
    override suspend fun getEntries(): MutableList<Entry>
    {
        return entries;
    }

    override suspend fun addEntry(entry: Entry): Long
    {
        entries.add(entry)
        return (entries.size - 1).toLong()
    }

    override suspend fun deleteEntry(idx: Int)
    {
        entries.removeAt(idx)
    }

    override suspend fun editEntry(idx: Int, editedEntry: Entry) {
        entries[idx] = editedEntry
    }
}