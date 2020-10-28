package com.dei.mobile.dagger

import com.dei.mobile.activities.AddEditEntryActivity
import com.dei.mobile.activities.EntryDetailsActivity
import com.dei.mobile.activities.MainActivity
import dagger.Component
import javax.inject.Singleton

@Singleton
@Component(modules = [DependencyProducer::class])
interface DependencyGraph
{
    fun inject(mainActivity: MainActivity)

    fun inject(entryDetailsActivity: EntryDetailsActivity)

    fun inject(addEditEntryActivity: AddEditEntryActivity)
}