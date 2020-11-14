using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace AsyncTasks
{
    internal static class Program
    {
        private static void Main()
        {
            var stopwatch = new Stopwatch();
            var hosts = new List<string> {"en.wikipedia.org/wiki/Alan_Turing", "www.washingtonpost.com/", "google.com"};
            var executor = new AsyncTasksHttpExecutor(hosts);
            stopwatch.Start();
            executor.Execute();
            stopwatch.Stop();
            Console.WriteLine($"DURATION SECONDS {stopwatch.Elapsed.Seconds} MILLISECONDS {stopwatch.Elapsed.Milliseconds}");
        }
    }
}
