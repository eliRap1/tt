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
        public static byte[] sendAndReceive(byte[] data)
        {
            try
            {
                using (TcpClient client = new TcpClient())
                {
                    client.Connect(SERVER_IP, SERVER_PORT);

                    using (NetworkStream stream = client.GetStream())
                    {
                        stream.Write(data, 0, data.Length);
                        using (MemoryStream ms = new MemoryStream())
                        {
                            byte[] buffer = new byte[1024];
                            int bytesRead;
                            stream.ReadTimeout = 2000; // 2 SEC
                            bytesRead = stream.Read(buffer, 0, buffer.Length);
                            
                             Console.WriteLine($"Received {bytesRead} bytes");
                             ms.Write(buffer, 0, bytesRead);
                            

                            Console.WriteLine("Finished reading from stream.");
                            return ms.ToArray();
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                throw new Exception("Communication with server failed: " + ex.Message);
            }
        }
    }
}
