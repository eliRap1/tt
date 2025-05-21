using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.IO;

namespace client
{
    public class Communicator
    {
        private const string SERVER_IP = "127.0.0.1";
        private const int SERVER_PORT = 3353;
        private TcpClient client;
        private NetworkStream stream;
        public Communicator(TcpClient client) {this.client = client;}
        public void close() { this.client.Close(); }
        public void connect() { this.client.Connect(SERVER_IP, SERVER_PORT); this.stream = this.client.GetStream(); }
        public byte[] sendAndReceive(byte[] data)
        {
            try
            {
                        
                        this.stream.Write(data, 0, data.Length);
                        using (MemoryStream ms = new MemoryStream())
                        {
                            byte[] buffer = new byte[1024];
                            int bytesRead;
                            this.stream.ReadTimeout = 2000; // 2 SEC
                            bytesRead = this.stream.Read(buffer, 0, buffer.Length);
                            
                             Console.WriteLine($"Received {bytesRead} bytes");
                             ms.Write(buffer, 0, bytesRead);
                            

                            Console.WriteLine("Finished reading from stream.");
                            return ms.ToArray();
                        }
                    
                
            }
            catch (Exception ex)
            {
                throw new Exception("Communication with server failed: " + ex.Message);
            }
        }
    }
}
