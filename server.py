#!/usr/bin/env python3
# -*- coding: utf8 -*-
'''
    Simple socket server using threads
'''

import socket
import sys
import threading
import time

HOST = ''   # Symbolic name meaning all available interfaces
PORT = 8888 # Arbitrary non-privileged port
quit = False

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

def incomingMsg(conn):
    #Sending message to connected client
    conn.send(b'Welcome to the PixTudio debug server.\0')

    #infinite loop so that function do not terminate and thread do not end.
    while not quit:
        #Receiving from client
        data = conn.recv(1024)
        reply = b'ACK\0'
        if not data or data.decode('UTF8').strip() in ('exit', 'quit'):
            break
        else:
            print(data)

        conn.sendall(reply)

    print("Connection closed")
    #came out of loop
    conn.close()

def outgoingMsg(conn):
    while not quit:
        command = sys.stdin.readline().strip()
        conn.sendall(command.encode('UTF8')+b'\0')
        sys.stdout.write('> ')


#wait to accept a connection - blocking call
conn, addr = s.accept()
print('Connected with ' + addr[0] + ':' + str(addr[1]))

# Start a new thread to process commands
t1 = threading.Thread(target=incomingMsg, args=(conn,))
t1.daemon=True
t1.start()
t2 = threading.Thread(target=outgoingMsg, args=(conn,))
t2.daemon=True
t2.start()
while t1.is_alive() and t2.is_alive():
    time.sleep(1)

# Close the socket
s.close()

# Quit
sys.exit(0)
