import os
import sys
import json
import socket
import random
from threading import Thread



#Klassen


class ClientThread(Thread):
    
    def __init__(self, connection, address):
        Thread.__init__(self);
        self.connection = connection;
        self.address = address;
        self.start();
        
    def send(self, msg):
        self.connection.sendall((msg + "\n").encode("utf-8"));
        
    def run(self):
        global WORLD;
        print("[THREAD] Client verbunden " + str(self.address));
        self.send("CONN ACTIVE");
        while True:
            command = self.connection.recv(32).decode('utf-8');
            split = command.split(" ");
            if(split[0]=='MAP'):
                if(split[1]=='GET'):
                    for each in WORLD.getAll():
                        self.send(each);
        
class MapTile:
    
    def __init__(self):
        self.rotation = 0;
        self.tileType = 'GRASS';
    
    def setType(self, pType):
        self.tileType = pType;
    
    def setRotation(self, pRotation):
        self.rotation = pRotation;
        
        
class World:
    
    def __init__(self):
        self.data = [];
        self.generate();
        
    def getAll(self):
        global CONFIG;
        yield "MAP BEGIN";
        for x in range(CONFIG['world']['size']):
            for y in range(CONFIG['world']['size']):
                yield self.data[x][y].tileType + ' ' + str(self.data[x][y].rotation);
        yield "MAP END";
        
    def generate(self):
        global CONFIG;
        print(CONFIG);
        self.data = [];
        print("[WELT] Welt wird generiert...");
        for x in range(CONFIG['world']['size']):
            self.data.append(list());
            for y in range(CONFIG['world']['size']):
                tile = MapTile();
                if(random.random()>0.8):
                    tile.setType('FORREST');
                else:
                    tile.setType('GRASS');
                tile.setRotation(random.randint(0,3));
                self.data[x].append(tile);
        
            












#MAIN

def log(msg):
    print("[SERVER] " + msg);

DEFAULT_CONFIG = {
    'bind_ip': 'localhost',
    'bind_port': 50505,
    'world': {
        'size': 300
    }
}

if(not os.path.exists('config.json')):
    with open('config.json', 'w') as file:
        file.write(json.dumps(DEFAULT_CONFIG, indent=4));
        file.flush();
    log("Erster Start.");
    log("Die Konfigurationsdatei wurde angelegt");
    log("Konfigurieren sie den Server und starten sie die Anwendung neu.");
    sys.exit(0);
    

global CONFIG;

with open('config.json') as file:
    CONFIG = json.loads(file.read());

log("Konfiguration: ");
print(CONFIG);

global WORLD;
WORLD = World();

clients = list();

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM);
sock.bind((CONFIG['bind_ip'], CONFIG['bind_port']));
sock.listen();

log("Server gestartet.");
while True:
    log("Es wird auf eine Verbindung gewartet.");
    conn,address = sock.accept();
    thread = ClientThread(conn,address);
    clients.append(thread);
