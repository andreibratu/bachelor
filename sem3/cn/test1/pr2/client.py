'''
6. The client sends to the server a string and a character.
The server returns to the client a list of all positions in the
string where specified character is found.
'''

import socket

query = input('Input a query for server: ')
char = input('Input character to look for in query: ')
server = ('127.0.0.1', 5555)

assert len(char) == 1

socket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

length = len(query)
socket.sendto(length.to_bytes(4, byteorder='big'), server)
socket.sendto(query.encode(), server)
socket.sendto(char.encode(), server)

buff, _ = socket.recvfrom(4)
numbers = int.from_bytes(buff, byteorder='big')
occs = []
print(f'Expecting {numbers} occurences..')

while numbers != 0:
    buff, _ = socket.recvfrom(4)
    x = int.from_bytes(buff, byteorder='big')
    occs.append(x)
    numbers -= 1

print(occs)
