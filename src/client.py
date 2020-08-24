#!/usr/bin/env python3

import socket

if __name__ == "__main__":
    IP = "127.0.0.1"
    PORT = 9998
    MSG = b"Hello World"

    print("UDP IP:{}".format(IP))
    print("UDP PORT:{}".format(PORT))
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    print("Message is sending")
    sock.sendto(MSG, (IP, PORT))
    print("Message is sent...")
