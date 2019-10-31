import os
import sys
import json
import socket
import random
from threading import Thread
import time



#Klassen

class Player():
    
    def __init__(self):
        self.money = 2000;

class ClientThread(Thread):
    
    def __init__(self, connection, address):
        Thread.__init__(self);
        self.connection = connection;
        self.address = address;
        self.player = Player();
        self.start();
        
        
        
    def send(self, msg):
        self.connection.sendall((msg + "+").encode("utf-8"));
        
    def run(self):
        global WORLD,CONFIG;
        print("[THREAD] Client verbunden " + str(self.address));
        self.send("CONN ACTIVE");
        while True:
            command = self.connection.recv(32).decode('utf-8');
            split = command.split(" ");
            if(split[0]=='MAP'):
                if(split[1]=='GET'):
                    print("[THREAD] Sending Map to " + str(self.address));
                    for each in WORLD.getAll():
                        self.send(each);
                    self.send("MONEY " + str(self.player.money));
        
class MapTile:
    
    TYPES = {
        'GRASS': 0,
        'FORREST': 1,
        'CITY': 2,
        'RIVER_H': 3,
        'RIVER_V': 4,
        'RIVER_LB': 5,
        'RIVER_LT': 6,
        'RIVER_RT': 7,
        'RIVER_RB': 8,
        'RAIL_H': 9
    }
    
    def __init__(self):
        self.rotation = 0;
        self.tileType = 0;
    
    def setType(self, pType):
        self.tileType = MapTile.TYPES[pType];
    
    def setRotation(self, pRotation):
        self.rotation = pRotation;
        
        
class World:
    
    def __init__(self):
        self.data = [];
        self.generate();
        
    def getAll(self):
        global CONFIG;
        for x in range(CONFIG['world']['size']):
            for y in range(CONFIG['world']['size']):
                if(self.data[x][y].tileType != 0):
                    yield "TILE " + str(x) + " " + str(y) + " " + str(self.data[x][y].tileType) + " " + str(self.data[x][y].rotation);
        
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
                     
        for i in range(CONFIG['world']['size']):
            townSize = random.randint(2,20);
            posX = random.randint(0,CONFIG['world']['size']-1);
            posY = random.randint(0,CONFIG['world']['size']-1);
            for y in range(townSize):
                if(y==townSize/2):
                    pass;
                self.data[posX][posY].setType('CITY');
                self.data[posX][posY].setRotation(random.randint(0,3));
                posX+=random.randint(-1,1);
                posY+=random.randint(-1,1);
                if(posX<0):
                    posX=0;
                elif(posX>=CONFIG['world']['size']):
                    posX=CONFIG['world']['size']-1;
                if(posY<0):
                    posY=0;
                elif(posY>=CONFIG['world']['size']):
                    posY=CONFIG['world']['size']-1;
                
        
            












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
