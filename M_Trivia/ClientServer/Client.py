import socket

def communicate(client_socket):
    # Connect to the server
    response = ""
    try:
        response = client_socket.recv(5)
        print(f"Received: {response}")
    except Exception as error:
        print(f"Error: {error}")

    if response == b"Hello":
        try:
            message = b"Hello"
            client_socket.sendall(message)
            print(f"Sent: {message.decode()}")
        except Exception as error:
            print(f"Error: {error}")
    
    while True:
        None
    client_socket.close()


def main():
    port = int(input("Enter port: "))
    IP = "127.0.0.1"
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = (IP, port)
    try:
        client_socket.connect(server_address)
    except Exception as error:
            print(f"Error: {error}")
    print(f"Connected to {IP}:{port}")
    communicate(client_socket)


if __name__ == "__main__":
    main()

