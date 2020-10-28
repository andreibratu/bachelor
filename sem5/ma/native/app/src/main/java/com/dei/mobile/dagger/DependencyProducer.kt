package com.dei.mobile.dagger

import android.content.Context
import androidx.room.Room
import com.dei.mobile.domain.Entry
import com.dei.mobile.repositories.DatabaseRepository
import com.dei.mobile.repositories.InMemoryRepository
import com.dei.mobile.repositories.Repository
import com.dei.mobile.repositories.database.AppDatabase
import com.dei.mobile.services.DateService
import com.dei.mobile.services.EntryService
import dagger.Module
import dagger.Provides
import javax.inject.Singleton

@Module
class DependencyProducer(private val applicationContext: Context)
{
    @Provides
    @Singleton
    fun provideRepository(): Repository =
        DatabaseRepository(provideDatabaseObject())

    @Provides
    @Singleton
    fun provideEntityService(): EntryService = EntryService(provideRepository())

    @Provides
    @Singleton
        fun provideDatabaseObject(): AppDatabase = Room.databaseBuilder(
            applicationContext,
            AppDatabase::class.java, "entries-database"
        ).allowMainThreadQueries().fallbackToDestructiveMigration().build()
}