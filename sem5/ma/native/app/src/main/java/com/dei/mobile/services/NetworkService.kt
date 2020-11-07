package com.dei.mobile.services

import com.dei.mobile.domain.Entry
import io.ktor.client.*
import io.ktor.client.engine.cio.*
import io.ktor.client.request.*
import io.ktor.client.response.*
import io.ktor.util.*
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.async
import kotlinx.coroutines.io.jvm.javaio.toInputStream
import kotlinx.coroutines.runBlocking
import kotlinx.coroutines.withContext
import org.json.simple.JSONArray
import org.json.simple.JSONObject
import org.json.simple.parser.JSONParser
import java.io.InputStreamReader
import java.util.*
import java.util.stream.Collectors
import javax.inject.Singleton


@KtorExperimentalAPI
@Singleton
class NetworkService
{
    private val serverUrl = "https://chilling-werewolf-25891.herokuapp.com/api/entries"
    private val httpClient = HttpClient(CIO)
    private val parser = JSONParser()

    private fun jsonToEntry(obj: JSONObject) : Entry {
        val calendar = Calendar.getInstance()
        calendar.timeInMillis = obj["entry_date"] as Long
        return Entry(
            Math.toIntExact(obj["uid"] as Long),
            obj["entry_title"] as String,
            obj["entry_text"] as String,
            calendar,
            Math.toIntExact(obj["color_mask"] as Long)
        )
    }

    private fun entryToJson(obj: Entry) : String {
        val json = JSONObject()
        json["uid"] = obj.uid
        json["entry_title"] = obj.entryTitle
        json["entry_text"] = obj.entryText
        json["entry_date"] = obj.entryDate.timeInMillis
        json["color_mask"] = obj.color
        return json.toJSONString()
    }

    fun isServerUp(): Boolean = runBlocking {
        val defer = async(Dispatchers.IO) {
            httpClient.get<HttpResponse>(serverUrl) {
            }
        }
        return@runBlocking defer.await().status.value == 200
    }

    fun synchronise(localEntries: List<Entry>) {
        val serverIds = getEntries()!!.stream().map { it.uid }.collect(Collectors.toSet())
        val localIds = localEntries.stream().map { it.uid }.collect(Collectors.toSet())
        localIds.removeAll(serverIds)
        localEntries.forEach {
            if(localIds.contains(it.uid))
            {
                postEntry(it)
            }
        }
    }

    private fun getEntries(): List<Entry>? = runBlocking {
        val entries = mutableListOf<Entry>()
        if(!isServerUp()) return@runBlocking null
        val response = withContext(Dispatchers.IO) {
            httpClient.get<HttpResponse>(serverUrl)
        }
        val body = parser.parse(InputStreamReader(response.content.toInputStream())) as JSONArray
        for (i in 0 until body.size) {
            val obj = body[i] as JSONObject
            entries.add(jsonToEntry(obj))
        }
        entries as List<Entry>
    }

    fun postEntry(entry: Entry) = runBlocking {
        if(!isServerUp()) return@runBlocking null
        val response = withContext(Dispatchers.IO) {
            httpClient.post<HttpResponse>(serverUrl) {
                body = entryToJson(entry)
            }
        }
        val obj = parser.parse(InputStreamReader(response.content.toInputStream())) as JSONObject
        return@runBlocking jsonToEntry(obj)
    }

    fun deleteEntry(uid: Int) = runBlocking {
        if(!isServerUp()) return@runBlocking null
        val response = withContext(Dispatchers.IO) {
            httpClient.delete<HttpResponse>("$serverUrl/${uid}")
        }
        return@runBlocking response.status.value == 200
    }

    fun updateEntry(entry: Entry) = runBlocking {
        if(!isServerUp()) return@runBlocking null
        withContext(Dispatchers.IO) {
            httpClient.put<HttpResponse>("$serverUrl/${entry.uid}") {
                body = entryToJson(entry)
            }
        }
        return@runBlocking entry
    }
}