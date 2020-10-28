package com.dei.mobile.repositories

import com.dei.mobile.domain.Entry
import javax.inject.Singleton

@Singleton
class InMemoryRepository constructor(private val entries: MutableList<Entry>) : Repository
{
    override fun getEntries(): MutableList<Entry>
    {
        return entries
    }

    override fun addEntry(entry: Entry)
    {
        entries.add(entry)
    }

    override fun deleteEntry(idx: Int)
    {
        entries.removeAt(idx)
    }

    override fun editEntry(idx: Int, editedEntry: Entry) {
        entries[idx] = editedEntry
    }
}