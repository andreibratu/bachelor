package com.dei.mobile.repositories

import com.dei.mobile.domain.Entry

interface Repository
{
    fun getEntries(): MutableList<Entry>

    fun addEntry(entry: Entry)

    fun deleteEntry(idx: Int)

    fun editEntry(idx: Int, editedEntry: Entry)
}