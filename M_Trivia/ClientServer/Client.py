import socket

PORT = 5554
IP = "127.0.0.1"

def create_client_socket(server_ip, port):
    # Create a socket and connect to the server
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    return sock

def communicate(client_socket):
    # Send "Hello" and receive response
    server_address = (IP, PORT)
    client_socket.connect(server_address)
    for i in range(5):
        client_socket.send(b"Hello")
    while True:
        None


def main():
    #Client Build
    client_socket = create_client_socket(IP, PORT)
    communicate(client_socket)




if __name__ == "__main__":
    main()

