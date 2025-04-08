import socket
HOST = '127.0.0.1'
PORT = 3353
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    try:
        s.connect((HOST, PORT))
    except ConnectionRefusedError:
        print("Connection has failed to the server")
    else:
        data = s.recv(1024)
        data_to_send = data
        if "Hello" ==  data.decode():
            print(f"Sending: {data}")
            binary_data = data_to_send#.encode('utf-8')
            s.sendall(binary_data)
        else:
            print("Server suppose to write Hello")