using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace AsyncTasks
{
    public class AsyncTasksHttpExecutor
    {
        private readonly List<string> _hosts;
        private readonly List<Task> _tasks;

        public AsyncTasksHttpExecutor(List<string> hosts)
        {
            this._hosts = hosts;
            this._tasks = new List<Task>();
        }

        public void Execute()
        {
            for(var i = 0; i < _hosts.Count; i++)
            {
                _tasks.Add(Task.Factory.StartNew(Fetch, (_hosts[i], i)));
            }

            Task.WaitAll(_tasks.ToArray());
        }

        private static async void Fetch(object args)
        {
            var host = ((ValueTuple<string, int>) args).Item1;
            var id = ((ValueTuple<string, int>) args).Item2;

            // ReSharper disable once MethodHasAsyncOverload
            var hostInfo = Dns.GetHostEntry(host.Split('/')[0]);
            var ipAddress = hostInfo.AddressList[0];

            var remoteEndpoint = new IPEndPoint(ipAddress, HttpParser.Port);

            var clientSocket = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            var request = new RequestWrapper
            {
                Socket = clientSocket,
                Hostname = host.Split('/')[0],
                Endpoint = host.Contains("/") ? host.Substring(host.IndexOf("/", StringComparison.Ordinal)) : "/",
                RemoteEndPoint = remoteEndpoint,
                Id = id
            };

            await BeginConnection(request);

            await RequestData(request, HttpParser.GetRequestString(request.Hostname, request.Endpoint));

            await ReceiveData(request);
            
            Console.WriteLine(
                "{0} --> Response received : expected {1} chars in body, got {2} chars (headers + body)", 
                id, HttpParser.GetContentLength(request.ResponseContent.ToString()), request.ResponseContent.Length);
            
            clientSocket.Shutdown(SocketShutdown.Both);
            clientSocket.Close();
        }

        private static async Task ReceiveData(RequestWrapper request) {
            request.Socket.BeginReceive(request.Buffer, 0, RequestWrapper.BufferSize, 0, ReceiveCallback, request);

            await Task.FromResult<object>(request.ReceivedFlag.WaitOne());
        }

        private static void ReceiveCallback(IAsyncResult ar)
        {
            // Retrieve the details from the connection information wrapper
            var state = (RequestWrapper) ar.AsyncState;
            if (state == null) return;
            var clientSocket = state.Socket;

            try {
                // Read data from server
                var bytesRead = clientSocket.EndReceive(ar);

                // Read amount of characters equal to buffer or less
                state.ResponseContent.Append(Encoding.ASCII.GetString(state.Buffer, 0, bytesRead));

                // Call function recursively until header is obtained
                if (!HttpParser.ResponseHeaderObtained(state.ResponseContent.ToString())) {
                    clientSocket.BeginReceive(state.Buffer, 0, RequestWrapper.BufferSize, 0, ReceiveCallback, state);
                } else {
                    var responseBody = HttpParser.GetResponseBody(state.ResponseContent.ToString());

                    // Use response headers to calculate how much is left to read from body
                    if (responseBody.Length < HttpParser.GetContentLength(state.ResponseContent.ToString())) {
                        clientSocket.BeginReceive(state.Buffer, 0, RequestWrapper.BufferSize, 0, ReceiveCallback, state);
                    } else {
                        // All data has been received  
                        state.ReceivedFlag.Set();
                    }
                }
            } catch (Exception e) {
                Console.WriteLine(e.ToString());
            }
        }

        private static async Task RequestData(RequestWrapper request, string data)
        {
            var bytes = Encoding.ASCII.GetBytes(data);
            request.Socket.BeginSend(bytes, 0, bytes.Length, 0, OnDataSentCallback, request);
            await Task.FromResult<object>(request.SentFlag.WaitOne());
        }

        private static void OnDataSentCallback(IAsyncResult ar)
        {
            var state = (RequestWrapper) ar.AsyncState;
            if (state == null) return;
            var clientSocket = state.Socket;
            var clientId = state.Id;

            // complete sending the data to the server  
            var bytesSent = clientSocket.EndSend(ar);
            Console.WriteLine("{0} --> Sent {1} bytes to server.", clientId, bytesSent);

            // signal that all bytes have been sent
            state.SentFlag.Set();
        }
        
        private static async Task BeginConnection(RequestWrapper request) {
            request.Socket.BeginConnect(request.RemoteEndPoint, OnConnectionCallback, request);

            await Task.FromResult<object>(request.ConnectionFlag.WaitOne());
        }
        
        private static void OnConnectionCallback(IAsyncResult ar) {
            // retrieve the details from the connection information wrapper
            var state = (RequestWrapper) ar.AsyncState;
            if (state == null) return;
            var clientSocket = state.Socket;
            var clientId = state.Id;
            var hostname = state.Hostname;

            // complete the connection  
            clientSocket.EndConnect(ar);

            Console.WriteLine("{0} --> Socket connected to {1} ({2})", clientId, hostname, clientSocket.RemoteEndPoint);
            // signal that the connection has been made 
            state.ConnectionFlag.Set();
        }
    }
}