using ClientApp.Models.Responses;
using ClientApp.Views.Pages;
using System.Net;
using System.Windows;
using System.Net.Sockets;
using System.Windows.Navigation;

namespace ClientApp.Services
{
    public class SocketService
    {
        private static Socket _socket;
        private static string _ipAddress;
        private static int _port;


        public static void Initialize(string ipAddress, int port)
        {
            _ipAddress = ipAddress;
            _port = port;
            _socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

        }
        public static void Connect()
        {
            _socket.Connect(_ipAddress, _port);
        }

        public static async Task SendDataAsync(ArraySegment<byte> data)
        {
            if (_socket == null || !_socket.Connected)
                throw new InvalidOperationException("Socket is not connected.");
            await _socket.SendAsync(data, SocketFlags.None);

        }

        public static async Task<byte[]> ReceiveDataAsync(int amount)
        {
            if (_socket == null || !_socket.Connected)
                throw new InvalidOperationException("Socket is not connected.");

            var buffer = new byte[amount];
            int totalBytesRead = 0;

            while (totalBytesRead < amount)
            {
                int bytesRead = await _socket.ReceiveAsync(new ArraySegment<byte>(buffer, totalBytesRead, amount - totalBytesRead), SocketFlags.None);
                if (bytesRead == 0)
                    throw new SocketException((int)SocketError.ConnectionReset); // Connection closed by the peer

                totalBytesRead += bytesRead;
            }


            return buffer;
        }

        public static void CloseConnection()
        {
            _socket.Close();
        }
    }
}
