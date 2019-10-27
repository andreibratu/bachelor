'''
1. A client sends to the server an array of numbers.
Server returns the sum of the numbers.
'''

import socket

socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
socket.bind(("0.0.0.0", 5555))

print('Serving client..')
buff, addr = socket.recvfrom(4)
numbers = int.from_bytes(buff, byteorder='big')
print(f'Expecting {numbers} numbers')

sum = 0
while numbers != 0:
    buff, addr = socket.recvfrom(4)
    x = int.from_bytes(buff, byteorder='big')
    print(f'Received number {x}')
    sum += x
    numbers -= 1

print(f'Sum of given numbers is {sum}, sending..')
socket.sendto(sum.to_bytes(4, byteorder='big'), addr)
