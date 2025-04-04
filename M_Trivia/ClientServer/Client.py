import socket

PORT = 5554
IP = "127.0.0.1"

def create_client_socket(server_ip, port):
    # Create a socket and return it
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    return sock

def communicate(client_socket):
    # Connect to the server
    server_address = (IP, PORT)
    client_socket.connect(server_address)
    print(f"Connected to {IP}:{PORT}")

    for i in range(5):
        try:
            message = b"Hello"
            client_socket.sendall(message)
            print(f"Sent: {message.decode()}")
        except:
            print("Error: error sending message")
            break

        try:
            response = client_socket.recv(1024)
            print(f"Received: {response.decode()}")
        except:
            print("Error: error recieving message from server")
            break

    client_socket.close()


def main():
    #Client Build
    client_socket = create_client_socket(IP, PORT)
    communicate(client_socket)




if __name__ == "__main__":
    main()

