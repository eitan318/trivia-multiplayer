import socket
import time



def send_msg(client_sock, msg):
    try:
        client_sock.sendall((4).to_bytes(1, 'big'))
        client_sock.sendall(len(msg).to_bytes(4, 'big'))
        client_sock.sendall(msg.encode())
        print(f"Sent: {msg}")
    except Exception as error:
        print(f"Send error: {error}")
        return

def send_login_msg(client_sock, username, password):
    send_msg(client_sock, f'{{username: "{username}", password: "{password}"}}')

def send_signup_msg(client_sock, username, password, mail):
    send_msg(client_sock, f'{{username: "{username}", password: "{password}", mail: "{mail}"}}')

def communicate(client_socket):
    try:
        response = client_socket.recv(5)
        print(f"Received: {response.decode()}")
    except Exception as error:
        print(f"Receive error: {error}")
        return

    if response != b"Hello":
        return
    
    
    send_login_msg(client_socket, "primo", "123")
    try:
        response = client_socket.recv(100)
        print(f"Received: {response.decode()}")
    except Exception as error:
        print(f"Receive error: {error}")
        return
    
    send_signup_msg(client_socket, "primo", "123", "primo@gmail.com")
    try:
        response = client_socket.recv(100)
        print(f"Received: {response.decode()}")
    except Exception as error:
        print(f"Receive error: {error}")
        return

    # Simulate keeping the connection alive
    try:
        while input(":") != "EXIT":
            time.sleep(1)
    except KeyboardInterrupt:
        print("Interrupted. Closing connection.")


def main():
    IP = "127.0.0.1"
    try:
        port = int(input("Enter port: "))
    except ValueError:
        print("Invalid port.")
        return

    server_address = (IP, port)
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
            client_socket.connect(server_address)
            print(f"Connected to {IP}:{port}")
            communicate(client_socket)
    except Exception as error:
        print(f"Connection error: {error}")


if __name__ == "__main__":
    main()
