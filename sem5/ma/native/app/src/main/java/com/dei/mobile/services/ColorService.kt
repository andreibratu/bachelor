package com.dei.mobile.services

import android.graphics.Color

object ColorService
{
    fun getContrastingColor(backgroundARGB: Int): Int
    {
        val luminance = 1 - (
                0.299 * Color.red(backgroundARGB) +
                0.587 * Color.green(backgroundARGB) +
                0.114 * Color.blue(backgroundARGB)) / 255
        return if (luminance < 0.5) Color.BLACK else Color.WHITE
    }
}