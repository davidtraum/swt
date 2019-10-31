import socket
from threading import Thread
import sys


sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM);



if(len(sys.argv)>1):
    split = sys.argv[1].split(":");
    sock.connect((split[0], int(split[1])));
else:
    sock.connect((input("IP >> "), int(input("PORT>> "))));
    
class Receiver(Thread):
    
    def __init__(self):
        Thread.__init__(self);
        self.start();
        
    def run(self):
        while True:
            try:
                data = sock.recv(1024);
                if(data):
                    print(data);
                else:
                    print("no data");
            except Exception as e:
                print("ERR: " + str(e));
            
Receiver();
        
sock.sendall(b"MAP GET");
try:
    msg = input(">> ");
    if(len(msg)>0):
        sock.sendall(msg.encode('utf-8'));
except KeyboardInterrupt:
    pass;
sock.close();
