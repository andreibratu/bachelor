package com.dei.mobile.services

import com.dei.mobile.domain.Entry
import com.dei.mobile.domain.EntryDTO
import com.dei.mobile.repositories.Repository
import javax.inject.Singleton

@Singleton
class EntryService constructor(private val repository: Repository)
{
    private var entry: EntryDTO = EntryDTO(null, null, null, null, null)
    public var isCreate = true

    val entries: List<Entry>
        get() = repository.getEntries()

    fun deleteEntry(idx: Int)
    {
        repository.deleteEntry(idx)
    }

    fun setCurrentEntry(entry: EntryDTO)
    {
        this.entry = entry
    }

    fun getCurrentEntry(): EntryDTO?
    {
        return this.entry
    }

    fun submitEntry(currEntry: EntryDTO)
    {
        if (this.isCreate)
        {
            this.repository.addEntry(
                Entry(
                    0,
                    currEntry.entryTitle!!,
                    currEntry.entryText!!,
                    currEntry.entryDate!!,
                    currEntry.color!!)
            )
        }
        else
        {
            this.repository.editEntry(currEntry.position!!, Entry(
                null,
                currEntry.entryTitle!!,
                currEntry.entryText!!,
                currEntry.entryDate!!,
                currEntry.color!!
            ))
        }
    }
}