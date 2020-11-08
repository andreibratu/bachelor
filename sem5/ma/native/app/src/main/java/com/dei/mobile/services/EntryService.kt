package com.dei.mobile.services

import com.dei.mobile.domain.Entry
import com.dei.mobile.domain.EntryDTO
import com.dei.mobile.repositories.Repository
import javax.inject.Singleton

@Singleton
class EntryService constructor(private val repository: Repository)
{
    private var entry: EntryDTO = EntryDTO(null, null, null, null, null)
    var isCreate = true

    suspend fun getEntries(): List<Entry>
    {
        return repository.getEntries()
    }

    suspend fun deleteEntry(idx: Int)
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

    suspend fun submitEntry(currEntry: EntryDTO): Long
    {
        var id: Long
        if (isCreate)
        {
            val size = repository.getEntries().size
            id = repository.addEntry(
                Entry(
                    size,
                    currEntry.entryTitle!!,
                    currEntry.entryText!!,
                    currEntry.entryDate!!,
                    currEntry.color!!)
            )
        }
        else
        {
            id = currEntry.position!!.toLong()
            repository.editEntry(currEntry.position!!, Entry(
                null,
                currEntry.entryTitle!!,
                currEntry.entryText!!,
                currEntry.entryDate!!,
                currEntry.color!!
            ))
        }
        return id
    }
}