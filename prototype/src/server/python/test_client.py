import socket
from threading import Thread


sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM);

sock.connect((input("IP >> "), int(input("PORT>> "))));

class Receiver(Thread):
    
    def __init__(self):
        Thread.__init__(self);
        self.start();
        
    def run(self):
        while True:
            print(sock.recv(128));
            
Receiver();
        
try:
    msg = input(">> ");
    if(len(msg)>0):
        sock.sendall(msg.encode('utf-8'));
except KeyboardInterrupt:
    pass;
sock.close();
