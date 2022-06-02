import socket
import time

#config
port = 4444

#script
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("", port))
s.listen(5)
while True:
    (c, c_addr) = s.accept()
    time.sleep(10)