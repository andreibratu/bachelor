package com.dei.mobile.dagger

import android.app.Application
import com.dei.mobile.dagger.DaggerDependencyGraph
import com.dei.mobile.dagger.DependencyGraph
import com.dei.mobile.dagger.DependencyProducer

class DIApplication : Application()
{
    var dependencyGraph: DependencyGraph = DaggerDependencyGraph.builder()
        .dependencyProducer(DependencyProducer(this))
        .build()
}