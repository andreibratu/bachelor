package com.dei.mobile.services

import java.text.DateFormat
import java.text.SimpleDateFormat
import java.util.*

object DateService
{
    fun buildCalendar(year: Int, month: Int, date: Int): Calendar
    {
        val calendar = Calendar.getInstance()
        calendar[Calendar.YEAR] = year
        calendar[Calendar.MONTH] = month
        calendar[Calendar.DATE] = date
        return calendar
    }

    fun dateToString(date: Calendar) : String
    {
        val dateFormat: DateFormat = SimpleDateFormat("dd MMM", Locale.US)
        return dateFormat.format(date.time)
    }
}