#!/usr/bin/env python3
'''
    Simple socket server using threads
'''

import socket
import sys
import threading
import time

HOST = ''   # Symbolic name meaning all available interfaces
PORT = 8888 # Arbitrary non-privileged port

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print('Socket created')

#Bind socket to local host and port
try:
    s.bind((HOST, PORT))
except socket.error as msg:
    print('Bind failed. Error Code : ' + str(msg))
    sys.exit(1)

print('Socket bind complete')

#Start listening on socket
s.listen(10)
print('Socket now listening')

#Function for handling connections. This will be used to create threads
def clientthread(conn):
    #Sending message to connected client
    conn.send(b'Welcome to the server. Type something and hit enter\n') #send only takes string

    #infinite loop so that function do not terminate and thread do not end.
    while True:
        #Receiving from client
        data = conn.recv(1024)
        reply = b'OK...' + data + b'\0'
        if not data or data.decode('UTF8').strip() in ('exit', 'quit'):
            break
        else:
            print("Got {}, sent {}".format(data, reply))

        conn.sendall(reply)

    print("Connection closed")
    #came out of loop
    conn.close()

#wait to accept a connection - blocking call
conn, addr = s.accept()
print('Connected with ' + addr[0] + ':' + str(addr[1]))

# Start a new thread to process commands
t = threading.Thread(target=clientthread, args=(conn,))
t.start()

# Wait for the thread to end
while threading.active_count() > 1:
    time.sleep(1)

# Close the socket
s.close()

# Quit
sys.exit(0)
