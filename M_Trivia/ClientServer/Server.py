import socket

IP = "127.0.0.1"  # Define server IP
PORT = 5554       # Ensure the server is listening on this port

def create_server_socket(ip, port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind((ip, port))  # Correct bind usage
    sock.listen(1)  # Start listening for connections
    print(f"Server listening on {ip}:{port}...")
    return sock

def listen():
    server_sock = create_server_socket(IP, PORT)
    client_socket, addr = server_sock.accept()  # Accept connection
    print(f"Connection from {addr}")
    while True:  # Keep server running
        data = client_socket.recv(5)  # Read 5 bytes
        print(data)

    client_socket.close()  # Close client connection

def main():
    listen()

if __name__ == "__main__":
    main()

