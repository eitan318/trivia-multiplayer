import socket

def handle_client(client_socket):
    initial_msg = b"Hello"
    client_socket.sendall(initial_msg)
    print(f"Sent {initial_msg}")
    while True:
        try:
            code = ord(client_socket.recv(1))  # Convert the byte to an integer
            
            if not code:
                print("Client disconnected")
                break
            
            msg_len = int.from_bytes(client_socket.recv(4), 'big')
            msg = client_socket.recv(msg_len).decode()

            client_socket.sendall(f"Received: code: {code} len: {msg_len} msg: {msg}".encode())
            print(f"Sent {initial_msg}")
        except Exception as error:
            print("Error:", error)

    client_socket.close()  

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

