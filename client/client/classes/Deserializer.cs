using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace client
{
    public class Deserializer
    {
        public static int extractStatus(byte[] responseData)
        {
            string json = Encoding.UTF8.GetString(responseData);
            string key = "\"status\":";
            int index = json.IndexOf(key);
            if (index == -1)
                throw new Exception("Status field not found in response");

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
    }
}
