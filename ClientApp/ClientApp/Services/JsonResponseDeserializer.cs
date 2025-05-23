using Newtonsoft.Json;
using System.Text;
using ClientApp.Models.Responses;

namespace ClientApp.Services
{
    /// <summary>
    /// Provides functionality for deserializing JSON responses from the server.
    /// </summary>
    class JsonResponseDeserializer
    {
        /// <summary>
        /// Deserializes a JSON response into a specified type.
        /// </summary>
        /// <typeparam name="T">The type into which the JSON response should be deserialized.</typeparam>
        /// <param name="responseInfo">The response information containing the raw JSON data.</param>
        /// <returns>An object of type <typeparamref name="T"/> representing the deserialized response data.</returns>
        /// <exception cref="JsonException">
        /// Thrown if the JSON response cannot be deserialized into the specified type.
        /// </exception>
        internal T DeserializeResponse<T>(byte[] buffer)
        {
            // Convert the raw response buffer to a JSON string
            var json = Encoding.UTF8.GetString(buffer, 0, buffer.Length);

            // Deserialize the JSON string into the specified type
            T data = JsonConvert.DeserializeObject<T>(json);

            return data;
        }
    }
}
