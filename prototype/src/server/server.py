import json
import os
import socket
from threading import Thread
import time



class ClientThread(Thread):
    
    def __init__(self, pConnection):
        Thread.__init__(self);
        self.connection = pConnection;

    def run(self):
        while True:
            data = self.connection.recv(32);
            command = data.decode('utf-8');
            args = command.split(" ");
            if(args[0] == 'MAP'):


DEFAULT_CONFIG = {
    'port': 2000,
    'bind_ip': 'localhost',
    'max_players': 5};

CONFIG_FILE = 'config.json';

if not os.path.exists(CONFIG_FILE):
    print("Die Konfigurationsdatei wird angelegt...");
    with open(CONFIG_FILE, 'w') as file:
        json_string = json.dumps(DEFAULT_CONFIG, indent=4);
        file.write( json_string );
        file.flush();


CONFIG = None;
with open(CONFIG_FILE) as file:
    CONFIG = json.loads( file.read() );


server = socket.socket(socket.AF_INET, socket.SOCK_STREAM);
server.bind( (CONFIG['bind_ip'], CONFIG['port']) );
server.listen();

clients = [];

print("Server wird gestartet...");
print(CONFIG);

karte = [][];

try:
    while True:
        connection, address = server.accept();
        print("Verbindungsaufbau von " + str(address) + "...");
        thread = ClientThread(connection);
        thread.start();
        clients.append(thread);
                
except KeyboardInterrupt:
    print("Server beendet");






