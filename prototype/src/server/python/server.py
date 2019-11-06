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

class NotifierThread(Thread):

    def __init__(self):
        Thread.__init__(self);
        self.queue = [];
        self.start();

    def add(self, msg, pExcept):
        print("add to notifier");
        self.queue.append((msg, pExcept));

    def run(self):
        while True:
            try:
                if(len(self.queue)>0):
                    msg = self.queue.pop();
                    print("[NOTIFIER] Sending " + str(msg[0]));
                    for client in clients:
                        if(client != msg[1]):
                            try:
                                client.send(msg[0]);
                            except Exception:
                                pass;
            except Exception as e:
                print("Notifier error " +  str(e));


class ClientThread(Thread):
    
    def __init__(self, connection, address, pId):
        Thread.__init__(self);
        self.connection = connection;
        self.address = address;
        self.player = Player();
        self.clientId = pId;
        self.start();
        
        
    def send(self, msg):
        self.connection.send((msg + "~").encode("utf-8"));
        
    def sendAll(self, msg, exceptSelf=True):
        if(exceptSelf):
            notifier.add(msg, self);
        else:
            notifier.add(msg, None);
        
    def run(self):
        try:
            global WORLD,CONFIG,clients;
            print("[THREAD] Client verbunden " + str(self.address) + " ID: " + self.clientId);
            self.sendAll("P C " + self.clientId);
            while True:
                command = self.connection.recv(32).decode('utf-8'); 
                split = command.split(" ");
                if(split[0]=='M'):
                    if(split[1]=='G'):
                        print("[THREAD] Sending Map to " + str(self.address));
                        count = 0;
                        for each in WORLD.getAll():
                            self.send(each);
                            count+=len(each);
                        print("Transferred " + str(int(count/1000)) + "kb"); 
                        self.send("MONEY " + str(self.player.money));
                        for client in clients:
                            if(client!=self):
                                self.send("P C " + client.clientId);
                        self.send("M L");
                elif(split[0]=='P'):
                    print("[THREAD] Position update from " + str(self.address) + ": " + split[1] + " / " + split[2]);
                    self.sendAll("P P "  + self.clientId + " " + split[1] + " " + split[2]);
                elif(split[0]=='T'):
                    print("[THREAD] Tile change " + split[1] + " - " + split[2]);
                    WORLD.data[int(split[1])][int(split[2])].tileType = int(split[3]);
                    WORLD.data[int(split[1])][int(split[2])].setRotation(int(split[4]));
                    self.sendAll("T " + split[1] + " " + split[2] + " " + split[3] + " " + split[4]);
        except BrokenPipeError:
            if(self in clients):
                clients.remove(self);
            print("[THREAD] Disconnected " + str(self.address));
            print("[THREAD] Players online: " + str(len(clients)));
        
class City:
    counter = 0;
    
    def __init__(self):
        self.centerX = 0;
        self.centerY = 0;
        self.tiles = [];
        self.cityID = City.counter;
        City.counter+=1;
        
    def setCenter(self, pX,pY):
        self.centerX = pX;
        self.centerY = pY;
        
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
    
    def __init__(self, posX, posY):
        self.rotation = 0;
        self.tileType = 0;
        self.posX = posX;
        self.posY = posY;
    
    def setType(self, pType):
        self.tileType = MapTile.TYPES[pType];
    
    def setRotation(self, pRotation):
        self.rotation = pRotation;
        
    def isRiver(self):
        return self.tileType>2 and self.tileType<9;
        
        
class World:
    
    def __init__(self):
        self.data = [];
        self.cities = list();
        self.generate();
        
    def getAll(self):
        global CONFIG;
        for x in range(CONFIG['world']['size']):
            for y in range(CONFIG['world']['size']):
                if(self.data[x][y].tileType != 0):
                    yield "T " + str(x) + " " + str(y) + " " + str(self.data[x][y].tileType) + " " + str(self.data[x][y].rotation);
        for city in self.cities:
            yield "C C " + str(city.cityID) + " " + str(city.centerX) + " " + str(city.centerY);
            for tile in city.tiles:
                yield "C T " + str(city.cityID) + " " + str(tile.posX) + " " + str(tile.posY);
        
    def generate(self):
        global CONFIG;
        print(CONFIG);
        self.data = [];
        print("[WELT] Welt wird generiert...");
        for x in range(CONFIG['world']['size']):
            self.data.append(list());
            for y in range(CONFIG['world']['size']):
                tile = MapTile(x,y);
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
            city = City();
            for y in range(townSize):
                if(y==townSize/2):
                    city.setCenter(posX,posY);
                self.data[posX][posY].setType('CITY');
                self.data[posX][posY].setRotation(random.randint(0,3));
                city.tiles.append(self.data[posX][posY]);
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
            self.cities.append(city);
                    
        for i in range(random.randint(5, (CONFIG['world']['size']/6))):
            posX = random.randint(0, CONFIG['world']['size']-1);
            posY = random.randint(0, CONFIG['world']['size']-1);
            vx = 1;
            vy = 0;
            sinceCurve = 0;
            typ = 'RIVER_H';
            while(True):
                self.data[posX][posY].setType(typ);
                self.data[posX][posY].setRotation(0);
                posX+=vx;
                posY+=vy;
                sinceCurve+=1;
                if(sinceCurve>random.randint(2,8)):
                    if(random.random()>0.5):
                        if(vy==-1):
                            vy = 0;
                            vx = 1;
                            typ = 'RIVER_RB';
                        elif(vy==0):
                            if(vx==-1):
                                typ = 'RIVER_RT';
                            else:
                                typ = 'RIVER_LT';
                            vy = -1;
                            vx = 0;
                        else:
                            vy = 0;
                            vx = -1;
                            typ = 'RIVER_LT';
                    else:
                        if(vx==-1):
                            vy = 1;
                            vx = 0;
                            typ = 'RIVER_RB';
                        elif(vx==0):
                            if(vy==1):
                                typ = 'RIVER_LT';
                            else:
                                typ = 'RIVER_LB';
                            vy = 0;
                            vx = -1;
                        else:
                            vy = -1;
                            vx = 0;
                            typ = 'RIVER_LT';
                    sinceCurve = 0;
                else:
                    if(vy==0):
                        typ = 'RIVER_H';
                    else:
                        typ = 'RIVER_V';
                        
                if(not (posX>0 and posY>0 and posX<CONFIG['world']['size']-1 and posY<CONFIG['world']['size']-1 and not self.data[posX][posY].isRiver())):
                    break;
                
        
            












#MAIN

def log(msg):
    print("[SERVER] " + msg);

DEFAULT_CONFIG = {
    'bind_ip': 'localhost',
    'bind_port': 50505,
    'world': {
        'size': 300
    },
    'game': {
        'max_players': 10
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

global WORLD,clients,notifier;
WORLD = World();
notifier = NotifierThread();

clients = list();

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM);
sock.bind((CONFIG['bind_ip'], CONFIG['bind_port']));
sock.listen();

log("Server gestartet.");
while True:
    log("Es wird auf eine Verbindung gewartet.");
    conn,address = sock.accept();
    if(len(clients)<CONFIG['game']['max_players']):
        thread = ClientThread(conn,address,str(len(clients)));
        clients.append(thread);
    else:
        conn.close();
