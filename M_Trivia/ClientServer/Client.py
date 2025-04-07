import socket
import time
import json

def send_msg(client_sock, msg, code):
    try:
        data = code.to_bytes(1, 'big') + len(msg).to_bytes(4, 'big') + msg.encode('utf-8')
        client_sock.sendall(data)
    except Exception as error:
        print(f"Send error: {error}")

def send_login_msg(client_sock, username, password):
    msg = json.dumps({
        "username": username,
        "password": password
    })
    send_msg(client_sock, msg, 1)

def send_signup_msg(client_sock, username, password, mail, house_addr, phone_number, birth_date):
    msg = json.dumps({
        "username": username,
        "password": password,
        "email": mail,
        "house_address": house_addr,
        "phone_number": phone_number,
        "birth_date": birth_date
    })
    send_msg(client_sock, msg, 2)

def communicate(client_socket):
    try:
        response = client_socket.recv(5)
        print(f"Received: {response.decode()}")
    except Exception as error:
        print(f"Receive error: {error}")
        return

    if response != b"Hello":
        return
    
    client_socket.sendall(b"Hello")
    send_login_msg(client_socket, "primo2", "12345678Ab#")
    try:
        response = client_socket.recv(100)
        print(f"Received: {response.decode()}")
    except Exception as error:
        print(f"Receive error: {error}")
        return
    send_signup_msg(client_socket, "primo2", "12345678Ab#", "primo2@gmail.com", "brosh, 5, Netania", "054-2877748", "23/11/2008")
    try:
        response = client_socket.recv(100)
        print(f"Received: {response.decode()}")
    except Exception as error:
        print(f"Receive error: {error}")
        return
    send_login_msg(client_socket, "primo2", "12345678Ab#")  #trying to login again after signing up 
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
