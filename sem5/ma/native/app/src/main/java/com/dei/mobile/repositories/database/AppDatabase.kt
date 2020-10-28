package com.dei.mobile.repositories.database

import androidx.room.Database
import androidx.room.RoomDatabase
import androidx.room.TypeConverters
import com.dei.mobile.domain.Entry

@Database(entities = [Entry::class], version = 2)
@TypeConverters(Converters::class)
abstract class AppDatabase : RoomDatabase()
{
    abstract fun entityDao(): EntityDao
}