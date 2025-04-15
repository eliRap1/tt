import socket
import struct
import json
HOST = '127.0.0.1'
PORT = 3353
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    try:
        s.connect((HOST, PORT))
    except ConnectionRefusedError:
        print("Connection has failed to the server")
    else:
        header = s.recv(5)
        if len(header) < 5:
            print("Header is incomplete")
        else:
            code, length = struct.unpack('>BI', header)
            print(f"Code: {code}, Length: {length}")
            data = b""
            while len(data) < length:
                packet = s.recv(length - len(data))
                if not packet:
                    break
                data += packet
            try:
                message = json.loads(data.decode('utf-8'))
                print("Parsed JSON:", message)
            except json.JSONDecodeError:
                print("Failed to decode JSON.")