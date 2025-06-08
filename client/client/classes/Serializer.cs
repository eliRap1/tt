using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace client
{
    public class Serializer
    {
        private const int SIGNUP_CODE = 102;
        private const int LOGIN_CODE = 101;
        public static byte[] serializeSignupRequest(string username, string password, string email)
        {
            string json = "{"
                        + "\"username\":\"" + username + "\","
                        + "\"password\":\"" + password + "\","
                        + "\"email\":\"" + email + "\""
                        + "}";
            byte[] jsonBytes = Encoding.UTF8.GetBytes(json);
            int length = jsonBytes.Length;
            byte[] packet = new byte[1 + 4 + jsonBytes.Length];
            packet[0] = SIGNUP_CODE;
            packet[1] = (byte)((length >> 24) & 0xFF);
            packet[2] = (byte)((length >> 16) & 0xFF);
            packet[3] = (byte)((length >> 8) & 0xFF);
            packet[4] = (byte)(length & 0xFF);
            Buffer.BlockCopy(jsonBytes, 0, packet, 5, jsonBytes.Length);
            return packet;
        }
        public static byte[] serializeLoginRequest(string username, string password)
        {
            string json = "{"
                        + "\"username\":\"" + username + "\","
                        + "\"password\":\"" + password + "\""
                        + "}";

            byte[] jsonBytes = Encoding.UTF8.GetBytes(json);
            int length = jsonBytes.Length;
            byte[] packet = new byte[1 + 4 + jsonBytes.Length];
            packet[0] = LOGIN_CODE;
            packet[1] = (byte)((length >> 24) & 0xFF);
            packet[2] = (byte)((length >> 16) & 0xFF);
            packet[3] = (byte)((length >> 8) & 0xFF);
            packet[4] = (byte)(length & 0xFF);
            Buffer.BlockCopy(jsonBytes, 0, packet, 5, jsonBytes.Length);
            return packet;
        }
    }
}
