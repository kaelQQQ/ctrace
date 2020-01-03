import socket 
import time
import os
print os.getpid()
s = socket.socket()
host = "127.0.0.1"
port = 12345
while True:
    try:
        s.connect((host, port))
    except Exception as err:
        pass
    time.sleep(1)
    
