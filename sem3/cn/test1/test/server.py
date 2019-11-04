import socket
from threading import Thread

# Allow players to guess each other's number in pairs of two
# Server creates a room for each pair of players
# Multiple rooms can play at once

def sendInt(conn, value):
    # Send integer as 4 bytes, big endian assumed
    conn.send(value.to_bytes(4, byteorder='big'))

def receiveInt(conn):
    # Read 4 bytes, interpret as integer, big endian assumed
    return int.from_bytes(conn.recv(4), byteorder='big')

def gameLoop(conn_one, addr_one, conn_two, addr_two, room):
    # Assign to each player role of player one or two
    sendInt(conn_one, 0)
    sendInt(conn_two, 1)

    # Receive chosen numbers
    val1 = receiveInt(conn_one)
    val2 = receiveInt(conn_two)

    # Send start message to clients after receiving values
    sendInt(conn_one, 0)
    sendInt(conn_two, 0)

    print(f"Room {room}, received {val1} from one and {val2} from two")

    while True:
        guess1 = receiveInt(conn_one)
        print(f"Room {room} player one guess: {guess1}")
        if guess1 == val2:
            sendInt(conn_one, 0)
            sendInt(conn_two, 1)
            break
        else:
            sendInt(conn_one, 1)
            sendInt(conn_two, 0)
            guess2 = receiveInt(conn_two)
            print(f"Room {room} player two guess: {guess2}")
            if guess2 == val1:
                sendInt(conn_one, 1)
                sendInt(conn_two, 0)
                break
            else:
                sendInt(conn_one, 0)
                sendInt(conn_two, 1)

    # Cleanup
    conn_one.close()
    conn_two.close()


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

IP = "172.30.119.234"
PORT = 4444
room = 0

s.bind((IP, PORT))
s.listen(5)

print(f"Serving on {IP}, port {PORT}")

while True:
    conn_one, addr_one = s.accept()
    print(f"Room {room} player one connected..")
    conn_two, addr_two = s.accept()
    print(f"Room {room} player two connected..")
    args = (conn_one, addr_one, conn_two, addr_two, room)
    thread = Thread(target=gameLoop, args=args)
    thread.start()
    room += 1
