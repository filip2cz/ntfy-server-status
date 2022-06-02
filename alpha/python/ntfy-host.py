import socket
import time

#config
ipaddress = "192.168.1.107"
port = 4444

while True:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((ipaddress, port))
    s.close()
    time.sleep(3)
#created by Filip Komárek
#https://github.com/filip2cz/ntfy-server-status