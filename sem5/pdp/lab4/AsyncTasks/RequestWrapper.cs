using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

namespace AsyncTasks
{
    public class RequestWrapper
    {
        public Socket Socket = null;

        public const int BufferSize = 512;
        
        public readonly byte[] Buffer = new byte[BufferSize];

        public readonly StringBuilder ResponseContent = new StringBuilder();

        public int Id;
        public string Hostname;
        public string Endpoint;

        public IPEndPoint RemoteEndPoint;

        public readonly ManualResetEvent ConnectionFlag = new ManualResetEvent(false);
        public readonly ManualResetEvent SentFlag = new ManualResetEvent(false);
        public readonly ManualResetEvent ReceivedFlag = new ManualResetEvent(false);
    }
}