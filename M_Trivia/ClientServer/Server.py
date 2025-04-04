import socket

def handle_client(client_socket):
    initial_msg = b"Hello"
    client_socket.sendall(initial_msg)
    print(f"Sent {initial_msg}")
    try:
        data = client_socket.recv(5)
        if not data:
            print("Client disconnected")
        print("Received:", data.decode())
    except Exception as error:
        print("Error:", error)
    client_socket.close()  # Close client connection

def main():
    IP = "127.0.0.1" 
    PORT = 5554       
    server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_sock.bind((IP, PORT)) 
    server_sock.listen(1)  
    print(f"Server listening on {IP}:{PORT}...")
    client_socket, addr = server_sock.accept()
    print(f"Connection from {addr}")

    handle_client(client_socket)

if __name__ == "__main__":
    main()

