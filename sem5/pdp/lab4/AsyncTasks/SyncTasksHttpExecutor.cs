using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace AsyncTasks
{
    public class SyncTasksHttpExecutor
    {
        private readonly List<string> _hosts;
        private readonly List<Task> _tasks;

        public SyncTasksHttpExecutor(List<string> hosts)
        {
            this._hosts = hosts;
            this._tasks = new List<Task>();
        }

        public void Execute()
        {
            for (var i = 0; i < _hosts.Count; i++)
            {
                _tasks.Add(Task.Factory.StartNew(Fetch, (_hosts[i], i)));
            }

            Task.WaitAll(_tasks.ToArray());
        }

        private static void Fetch(object args)
        {
            var host = ((ValueTuple<string, int>) args).Item1;
            var id = ((ValueTuple<string, int>) args).Item2;
            
            var ipHostInfo = Dns.GetHostEntry(host.Split('/')[0]);
            var ipAddr = ipHostInfo.AddressList[0];
            var remoteEndpoint = new IPEndPoint(ipAddr, HttpParser.Port);
            
            var clientSocket = new Socket(ipAddr.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            var requestWrapper = new RequestWrapper
            {
                Socket = clientSocket,
                Hostname = host.Split('/')[0],
                Endpoint = host.Contains("/") ? host.Substring(host.IndexOf("/", StringComparison.Ordinal)) : "/",
                RemoteEndPoint = remoteEndpoint,
                Id = id
            };

            ConnectWrapper(requestWrapper).Wait();
            SendWrapper(requestWrapper, HttpParser.GetRequestString(requestWrapper.Hostname, requestWrapper.Endpoint)).Wait();
            ReceiveWrapper(requestWrapper).Wait();
            
            Console.WriteLine(
                "{0}) Response received : expected {1} chars in body, got {2} chars (headers + body)", 
                id, HttpParser.GetContentLength(requestWrapper.ResponseContent.ToString()), requestWrapper.ResponseContent.Length);

            // release the socket
            clientSocket.Shutdown(SocketShutdown.Both);
            clientSocket.Close();
        }
        
                private static Task ConnectWrapper(RequestWrapper requestWrapper) {
            requestWrapper.Socket.BeginConnect(requestWrapper.RemoteEndPoint, ConnectCallback, requestWrapper);

            return Task.FromResult(requestWrapper.ConnectionFlag.WaitOne());
        }

        private static void ConnectCallback(IAsyncResult ar) {
            // retrieve the details from the connection information wrapper
            var requestWrapper = (RequestWrapper) ar.AsyncState;
            if (requestWrapper != null)
            {
                var clientSocket = requestWrapper.Socket;
                var clientId = requestWrapper.Id;
                var hostname = requestWrapper.Hostname;

                // complete the connection  
                clientSocket.EndConnect(ar);

                Console.WriteLine("{0} --> Socket connected to {1} ({2})", clientId, hostname, clientSocket.RemoteEndPoint);
            }

            // signal that the connection has been made 
            requestWrapper?.ConnectionFlag.Set();
        }

        private static Task SendWrapper(RequestWrapper requestWrapper, string data) {
            // convert the string data to byte data using ASCII encoding.  
            var byteData = Encoding.ASCII.GetBytes(data);

            // begin sending the data to the server  
            requestWrapper.Socket.BeginSend(byteData, 0, byteData.Length, 0, SendCallback, requestWrapper);

            return Task.FromResult(requestWrapper.SentFlag.WaitOne());
        }

        private static void SendCallback(IAsyncResult ar) {
            var state = (RequestWrapper) ar.AsyncState;
            if (state != null)
            {
                var clientSocket = state.Socket;
                var clientId = state.Id;

                // complete sending the data to the server  
                var bytesSent = clientSocket.EndSend(ar);
                Console.WriteLine("{0} --> Sent {1} bytes to server.", clientId, bytesSent);
            }

            // signal that all bytes have been sent
            state?.SentFlag.Set();
        }

        private static Task ReceiveWrapper(RequestWrapper requestWrapper) {
            // begin receiving the data from the server
            requestWrapper.Socket.BeginReceive(requestWrapper.Buffer, 0, RequestWrapper.BufferSize, 0, ReceiveCallback, requestWrapper);

            return Task.FromResult(requestWrapper.ReceivedFlag.WaitOne());
        }

        private static void ReceiveCallback(IAsyncResult ar) {
            // retrieve the details from the connection information wrapper
            var requestWrapper = (RequestWrapper) ar.AsyncState;
            if (requestWrapper == null) return;
            var clientSocket = requestWrapper.Socket;

            try {
                var bytesRead = clientSocket.EndReceive(ar);
                requestWrapper.ResponseContent.Append(Encoding.ASCII.GetString(requestWrapper.Buffer, 0, bytesRead));

                // if the response header has not been fully obtained, get the next chunk of data
                if (!HttpParser.ResponseHeaderObtained(requestWrapper.ResponseContent.ToString()))
                {
                    clientSocket.BeginReceive(requestWrapper.Buffer, 0, RequestWrapper.BufferSize, 0, ReceiveCallback, requestWrapper);
                }
                else
                {
                    // header has been fully obtained
                    // get the body
                    var responseBody = HttpParser.GetResponseBody(requestWrapper.ResponseContent.ToString());

                    // the custom header parser is being used to check if the data received so far has the length
                    // specified in the response headers
                    if (responseBody.Length < HttpParser.GetContentLength(requestWrapper.ResponseContent.ToString()))
                    {
                        // if it isn't, than more data is to be retrieve
                        clientSocket.BeginReceive(requestWrapper.Buffer, 0, RequestWrapper.BufferSize, 0, ReceiveCallback, requestWrapper);
                    }
                    else
                    {
                        // otherwise, all the data has been received  
                        // signal that all bytes have been received  
                        requestWrapper.ReceivedFlag.Set();
                    }
                }
            } catch (Exception e) {
                Console.WriteLine(e.ToString());
            }
        }
    }
}