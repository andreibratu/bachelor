'''
3. A client sends to the server a string.
The server returns the reversed string to the client
'''

import socket

HOST = '127.0.0.1'
PORT = '5555'

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as socket:
    socket.bind((HOST, PORT))
    socket.listen()
    connection, addr = socket.accept()
    with connection:
        print('Connected by ', addr)
        length = int.from_bytes(connection.recv(4), byteorder='big')
        query = connection.recv(length).decode('ascii')
        connection.send(query[::-1].encode('ascii'))
