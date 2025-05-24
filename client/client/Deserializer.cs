using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

using Newtonsoft.Json;


namespace client
{
    public class Room
    {
        public int id { get; set; }
        public string name { get; set; }
        public int maxPlayers { get; set; }
        public int numOfQuestionsInGame { get; set; }
        public int timePerQuestion { get; set; }
    }

    public class GetRoomsResponse
    {
        public int status { get; set; }
        public List<Room> rooms { get; set; }
    }
    public class Deserializer
    {
        public static int extractStatus(byte[] responseData)
        {
            string json = Encoding.UTF8.GetString(responseData);
            string key = "\"status\":";
            int index = json.IndexOf(key);
            if (index == -1)
            {
                key = "\"message\"";
                string message = json.Substring(json.IndexOf(key) + key.Length + 2);
                message = message.Substring(0, message.IndexOf("\""));
                throw new Exception(message);
            }
                

            index += key.Length;
            string number = "";
            while (index < json.Length && char.IsDigit(json[index]))
            {
                number += json[index];
                index++;
            }

            if (int.TryParse(number, out int status))
            {
                return status;
            }
            throw new Exception("Invalid status value in response");
        }
        public static List<Room> DeserializeGetRoomsResponse(byte[] responseData)
        {
            const int headerSize = 5; // 4 byte fot json
            if (responseData.Length <= headerSize)
                return new List<Room>(); // not right response
            
            byte[] jsonBytes = responseData.Skip(headerSize).ToArray(); // skip the header

            string json = Encoding.UTF8.GetString(jsonBytes);

            try
            {
                var response = JsonConvert.DeserializeObject<GetRoomsResponse>(json);
                return response?.rooms ?? new List<Room>();
            }
            catch (Exception e)
            {
                MessageBox.Show($"error:{e.Message}", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return new List<Room>();
            }
        }

    }
}
