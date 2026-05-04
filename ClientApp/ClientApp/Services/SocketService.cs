using System;
using System.Net.Sockets;
using System.Threading.Tasks;

namespace ClientApp.Services
{
    /// <summary>
    /// Provides socket-based communication services for connecting to a server,
    /// sending, and receiving data.
    /// </summary>
    public class SocketService : IDisposable
    {
        private readonly Socket _socket;
        private string _ipAddress;
        private readonly int _port;
        private bool _disposed;

        /// <summary>
        /// Initializes the socket service with the specified server IP address and port number.
        /// </summary>
        /// <param name="ipAddress">The IP address of the server.</param>
        /// <param name="port">The port number to connect to on the server.</param>
        public SocketService(string ipAddress, int port)
        {
            _ipAddress = ipAddress;
            _port = port;
            _socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        }

        public void UpdateIpAddress(string ipAddress)
        {
            this._ipAddress = ipAddress;
        }

        /// <summary>
        /// Establishes a connection to the server using the initialized IP address and port.
        /// </summary>
        /// <exception cref="SocketException">Thrown if the connection fails.</exception>
        public void Connect()
        {
            _socket.Connect(_ipAddress, _port);
        }

        /// <summary>
        /// Sends data asynchronously to the server.
        /// </summary>
        /// <param name="data">The data to be sent as an <see cref="ArraySegment{T}"/> of bytes.</param>
        /// <returns>A task that represents the asynchronous send operation.</returns>
        /// <exception cref="InvalidOperationException">Thrown if the socket is not connected.</exception>
        public async Task SendDataAsync(ArraySegment<byte> data)
        {
            if (_socket == null || !_socket.Connected)
                throw new InvalidOperationException("Socket is not connected.");

            await _socket.SendAsync(data, SocketFlags.None);
        }

        /// <summary>
        /// Receives a specified amount of data asynchronously from the server.
        /// </summary>
        /// <param name="amount">The number of bytes to read from the server.</param>
        /// <returns>A task that represents the asynchronous receive operation. The task result contains the received data as a byte array.</returns>
        /// <exception cref="InvalidOperationException">Thrown if the socket is not connected.</exception>
        /// <exception cref="SocketException">Thrown if the connection is reset or closed by the server.</exception>
        public async Task<byte[]> ReceiveDataAsync(int amount)
        {
            if (_socket == null || !_socket.Connected)
                throw new InvalidOperationException("Socket is not connected.");

            var buffer = new byte[amount];
            int totalBytesRead = 0;

            while (totalBytesRead < amount)
            {
                int bytesRead = await _socket.ReceiveAsync(
                    new ArraySegment<byte>(buffer, totalBytesRead, amount - totalBytesRead), SocketFlags.None);

                if (bytesRead == 0)
                    throw new SocketException((int)SocketError.ConnectionReset); // Connection closed by the peer

                totalBytesRead += bytesRead;
            }

            return buffer;
        }

        /// <summary>
        /// Closes the socket connection to the server.
        /// </summary>
        public void CloseConnection()
        {
            _socket.Close();
        }

        /// <summary>
        /// Dispose pattern for releasing the socket resources.
        /// </summary>
        public void Dispose()
        {
            if (_disposed) return;

            try
            {
                _socket.Shutdown(SocketShutdown.Both);
            }
            catch { /* ignore errors on shutdown */ }

            _socket.Close();
            _socket.Dispose();
            _disposed = true;
        }
    }
}
