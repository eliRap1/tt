import socket
HOST = '127.0.0.1'
PORT = 3353
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    try:
        s.connect((HOST, PORT))
    except ConnectionRefusedError:
        print("Connection has failed to the server")
    else:
        data_to_send = input("enter 'Hello'")
        if data_to_send == "Hello":
            print(f"Sending: {data_to_send}")
            binary_data = data_to_send.encode('utf-8')
            s.sendall(binary_data)
            data = s.recv(1024)
            print(f"Received: {data}")
        else:
            print("you are suppose to write Hello")