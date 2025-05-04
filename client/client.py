import socket
import struct
import json

HOST = '127.0.0.1'
PORT = 3353
payload = {
    "username": "idan",
    "password": "9424idan",
    "email": "idan9464@gmail.com"
}
json_data = json.dumps(payload).encode('utf-8')
data_length = len(json_data)
code = 101
header = struct.pack('>BI', code, data_length)
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    try:
        s.connect((HOST, PORT))
        s.sendall(header + json_data)
        print("Login request sent.")
        response_header = s.recv(5)
        if len(response_header) < 5:
            print("Incomplete header received.")
        else:
            response_code, response_length = struct.unpack('>BI', response_header)
            print(f"Response code: {response_code}, length: {response_length}")
            response_data = b""
            while len(response_data) < response_length:
                chunk = s.recv(response_length - len(response_data))
                if not chunk:
                    break
                response_data += chunk
            try:
                parsed_response = json.loads(response_data.decode('utf-8'))
                print("Server response:", parsed_response)
            except json.JSONDecodeError:
                print("Failed to decode JSON from server.")
    except ConnectionRefusedError:
        print("Could not connect to the server.")
