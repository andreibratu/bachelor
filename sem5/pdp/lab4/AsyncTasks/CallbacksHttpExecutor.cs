using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

namespace AsyncTasks
{
    public class CallbacksHttpExecutor
    {
        private readonly List<string> _hosts;
        
        public CallbacksHttpExecutor(List<string> hosts)
        {
            this._hosts = hosts;
        }

        public void Execute()
        {
            for (var i = 0; i < this._hosts.Count; i++)
            {
                Fetch(this._hosts[i], i);
            }
        }
        
        private static void Fetch(string host, int id) {
            var ipHostInfo = Dns.GetHostEntry(host.Split('/')[0]);
            var ipAddress = ipHostInfo.AddressList[0];
            var remoteEndpoint = new IPEndPoint(ipAddress, HttpParser.Port);
            
            var clientSocket = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            var request  = new RequestWrapper
            {
                Socket = clientSocket,
                Hostname = host.Split('/')[0],
                Endpoint = host.Contains("/") ? host.Substring(host.IndexOf("/", StringComparison.Ordinal)) : "/",
                RemoteEndPoint = remoteEndpoint,
                Id = id
            };
 
            request.Socket.BeginConnect(request.RemoteEndPoint, ConnectedCallback, request);
        }

        private static void ConnectedCallback(IAsyncResult ar) {
            var requestWrapper = (RequestWrapper) ar.AsyncState;
            if (requestWrapper != null)
            {
                var clientSocket = requestWrapper.Socket;
                var clientId = requestWrapper.Id;
                var hostname = requestWrapper.Hostname;
                
                clientSocket.EndConnect(ar);
                Console.WriteLine("{0} --> Socket connected to {1} ({2})", clientId, hostname, clientSocket.RemoteEndPoint);
            }

            if (requestWrapper == null) return;
            var byteData = Encoding.ASCII.GetBytes(HttpParser.GetRequestString(
                requestWrapper.Hostname, 
                requestWrapper.Endpoint
            ));
            requestWrapper.Socket.BeginSend(byteData, 0, byteData.Length, 0, SentCallback, requestWrapper);
        }

        private static void SentCallback(IAsyncResult ar) {
            var requestWrapper = (RequestWrapper) ar.AsyncState;
            if (requestWrapper != null)
            {
                var clientSocket = requestWrapper.Socket;
                var clientId = requestWrapper.Id;
                var bytesSent = clientSocket.EndSend(ar);
                Console.WriteLine("{0} --> Sent {1} bytes to server.", clientId, bytesSent);
            }

            requestWrapper?.Socket.BeginReceive(requestWrapper.Buffer, 0, RequestWrapper.BufferSize, 0, ReceivedCallback,
                requestWrapper);
        }

        private static void ReceivedCallback(IAsyncResult ar) {
            var requestWrapper = (RequestWrapper) ar.AsyncState;
            if (requestWrapper == null) return;
            var clientSocket = requestWrapper.Socket;
            var clientId = requestWrapper.Id;

            try {
                var bytesRead = clientSocket.EndReceive(ar);
                requestWrapper.ResponseContent.Append(Encoding.ASCII.GetString(requestWrapper.Buffer, 0, bytesRead));
                
                if (!HttpParser.ResponseHeaderObtained(requestWrapper.ResponseContent.ToString())) {
                    clientSocket.BeginReceive(requestWrapper.Buffer, 0, RequestWrapper.BufferSize, 0, ReceivedCallback, requestWrapper);
                } else {
                    var responseBody = HttpParser.GetResponseBody(requestWrapper.ResponseContent.ToString());
                    
                    var contentLengthHeaderValue = HttpParser.GetContentLength(requestWrapper.ResponseContent.ToString());
                    if (responseBody.Length < contentLengthHeaderValue) {
                        clientSocket.BeginReceive(requestWrapper.Buffer, 0, RequestWrapper.BufferSize, 0, ReceivedCallback, requestWrapper);
                    } else {
                        foreach (var i in requestWrapper.ResponseContent.ToString().Split('\r', '\n'))
                            Console.WriteLine(i);
                        Console.WriteLine(
                            "{0} --> Response received : expected {1} chars in body, got {2} chars (headers + body)",
                            clientId, contentLengthHeaderValue, requestWrapper.ResponseContent.Length);
                        clientSocket.Shutdown(SocketShutdown.Both);
                        clientSocket.Close();
                    }
                }
            } catch (Exception e) {
                Console.WriteLine(e.ToString());
            }
        }
    }
}