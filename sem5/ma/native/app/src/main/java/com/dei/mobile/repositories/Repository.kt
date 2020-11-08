package com.dei.mobile.repositories

import com.dei.mobile.domain.Entry

interface Repository
{
    suspend fun getEntries(): MutableList<Entry>

    suspend fun addEntry(entry: Entry): Long

    suspend fun deleteEntry(idx: Int)

    suspend fun editEntry(idx: Int, editedEntry: Entry)
}