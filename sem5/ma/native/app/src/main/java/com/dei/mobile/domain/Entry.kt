package com.dei.mobile.domain

import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey
import java.util.*

@Entity(tableName = "entries")
class Entry(
    @PrimaryKey val uid: Int?,
    @ColumnInfo(name="entry_title") var entryTitle: String,
    @ColumnInfo(name="entry_text") var entryText: String,
    @ColumnInfo(name="entry_date") var entryDate: Calendar,
    @ColumnInfo(name="color_mask") var color: Int
)