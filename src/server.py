#!/usr/bin/env python3

import socket

if __name__ == "__main__":
    IP = "127.0.0.1"
    PORT = 9998

    print("Custom UDP socket server side...")
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((IP, PORT))
    print("Listening on HOST:{}, PORT:{}".format(IP, PORT))
    while 1:
        data, addr = sock.recvfrom(1024)
        print("Received message:{}".format(data))
