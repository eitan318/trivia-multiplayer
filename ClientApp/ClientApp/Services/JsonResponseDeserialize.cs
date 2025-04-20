using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ClientApp.Models.Responses;

namespace ClientApp.Services
{
    class JsonResponseDeserialize
    {
        static public T DeserializeResponse<T>(ResponseInfo responseInfo)
        {
            var json = Encoding.UTF8.GetString(responseInfo.Buffer, 0, responseInfo.Buffer.Length);
            T data = JsonConvert.DeserializeObject<T>(json);
            return data;
        }

    }
}
