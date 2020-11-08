package com.dei.mobile.dagger

import android.content.Context
import androidx.room.Room
import com.dei.mobile.repositories.DatabaseRepository
import com.dei.mobile.repositories.Repository
import com.dei.mobile.repositories.database.AppDatabase
import com.dei.mobile.services.EntryService
import com.dei.mobile.services.NetworkService
import dagger.Module
import dagger.Provides
import io.ktor.util.*
import javax.inject.Singleton

@Module
@KtorExperimentalAPI
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

    @Provides
    @Singleton
    fun provideNetworkService(): NetworkService = NetworkService()
}