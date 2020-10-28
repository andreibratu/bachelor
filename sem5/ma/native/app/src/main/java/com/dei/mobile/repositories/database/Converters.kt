package com.dei.mobile.repositories.database

import androidx.room.TypeConverter
import java.util.*

class Converters
{
    @TypeConverter
    fun fromTimestamp(value: Long?): Calendar?
    {
        val calendar = Calendar.getInstance()
        calendar.timeInMillis = value!!
        return calendar
    }

    @TypeConverter
    fun calendarToTimestamp(calendar: Calendar?): Long?
    {
        return calendar!!.timeInMillis
    }
}