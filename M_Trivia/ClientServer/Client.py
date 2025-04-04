import socket
import time


def communicate(client_socket):
    try:
        response = client_socket.recv(5)
        print(f"Received: {response.decode()}")
    except Exception as error:
        print(f"Receive error: {error}")
        return

    if response == b"Hello":
        try:
            message = "Hello".encode()
            client_socket.sendall(message)
            print(f"Sent: {message.decode()}")
        except Exception as error:
            print(f"Send error: {error}")
            return

    # Simulate keeping the connection alive
    try:
        while True:
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
