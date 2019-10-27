'''
8. The client sends to the server two arrays of integers.
The server returns an arrays containing common numbers found in both arrays.
'''

import socket

SERVER = ('127.0.0.1', '5555')

def readList(msg):
    return [int(x) for x in input(msg).split(' ') if len(x) > 0]

first_list = readList('Input first list: ')
second_list = readList('Input second list: ')

def sendInt(val, socket):
    socket.send(val.to_bytes(4, byteorder='big'))

def receiveInt(socket):
    return int.from_bytes(socket.recv(4), byteorder='big')

def sendList(list, socket):
    sendInt(len(list), socket)
    for x in list:
        sendInt(x, socket)

def receiveList(socket):
    nrs = receiveInt(socket)
    ans = []
    while nrs != 0:
        ans.append(receiveInt(socket))
        nrs -= 1
    return ans

with socket.create_connection(SERVER) as socket:
    sendList(first_list, socket)
    sendList(second_list, socket)

    answer = receiveList(socket)
    print(answer)
