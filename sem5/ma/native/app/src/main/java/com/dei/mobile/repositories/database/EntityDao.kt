package com.dei.mobile.repositories.database

import androidx.room.*
import com.dei.mobile.domain.Entry

@Dao
interface EntityDao
{
    @Query("SELECT * FROM entries")
    fun getAll(): List<Entry>

    @Update
    fun update(entry: Entry)

    @Insert
    fun insertAll(vararg entries: Entry): List<Long>

    @Query("UPDATE entries SET entry_title = :entry_title, entry_text = :entry_text, color_mask = :color_mask WHERE uid = :id")
    fun update(id: Int, entry_title: String, entry_text: String, color_mask: Int)

    @Delete
    fun delete(entry: Entry)
}