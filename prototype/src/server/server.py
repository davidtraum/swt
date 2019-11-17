import json
import os
import socket
from threading import Thread
import time
import random


class MapTile:

    TYPES = {
        'GRASS': 0,
        'FOREST': 1,
        'CITY': 2,
        'RIVER_H': 3,
        'RIVER_V': 4,
        'RIVER_LB': 5,
        'RIVER_LT': 6,
        'RIVER_RT': 7,
        'RIVER_RB': 8,
        'RAIL_H': 9
    }
    
    def __init__(self, pX, pY, pType):
        self.type = None;
        self.rotation = 0;
        self.x = pX;
        self.y = pY;
        self.setType(pType);

    def setType(self, pType):
        self.type = MapTile.TYPES[pType];

    def setRotation(self, pRotation):
        self.rotation = pRotation;
        
    def isRiver(self):
        return self.type>=3 and self.type<=8;

    def getProtocolString(self):
        return 'TILE ' + str(self.x) + ' ' + str(self.y) + ' ' + str(self.type) + ' ' + str(self.rotation);
    
class World:

    def __init__(self):
        self.data = [[MapTile(i,j, 'GRASS') for i in range(300)] for j in range(300)]

    def randomPosition(self):
        return (random.randint(0,299), random.randint(0,299));

    def isValidPosition(self, posX, posY):
        return posX>=0 and posY>=0 and posX<300 and posY<300;
    
    def generateWorld(self):
        print("Welt wird generiert...");
        size = 300;
        for x in range(size):
            for y in range(size):
                self.data[x][y].setRotation(random.randint(0,3));
                if(random.randint(0,100)<20):
                     self.data[x][y].setType('FOREST');
                     

        for townIndex in range(300):
            px,py = self.randomPosition();
            size = random.randint(3, 20);
            for houseIndex in range(size):
                self.data[px][py].setType('CITY');
                px += random.randint(-1,1);
                py += random.randint(-1,1);
                
                if(px < 0):
                    px = 0;
                elif(px > 299):
                    px = 299;

                if(py < 0):
                    py = 0;
                elif(py > 299):
                    py = 299;

        for riverIndex in range(20):
            px,py = self.randomPosition();
            vx = 1;
            vy = 0;
            sinceCurve = 0;
            typ = 'RIVER_H';
            while True:
                self.data[px][py].setType(typ);
                self.data[px][py].setRotation(0);
                px += vx;
                py += vy;
                sinceCurve+=1;
                if(sinceCurve > random.randint(3,10)):
                    if(random.random()>0.5):
                        if(vy == -1):
                            vy = 0;
                            vx = 1;
                            typ = 'RIVER_RB';
                        elif(vy == 0):
                            if(vx == -1):
                                typ = 'RIVER_RT';
                            else:
                                typ = 'RIVER_LT';
                            vy = -1;
                            vx = 0;
                        elif(vy == 1):
                            vy = 0;
                            vx = -1;
                    else:
                        if(vx == -1):
                            vy = 1;
                            vx = 0;
                            typ = 'RIVER_RB';
                        elif(vx == 0):
                            if(vy == 1):
                                typ = 'RIVER_LT';
                            else:
                                typ = 'RIVER_LB';
                            vy = 0;
                            vy = -1;
                        elif(vx == 1):
                            vy = -1;
                            vx = 0;
                            typ = 'RIVER_LT';
                    sinceCurve = 0;
                else:
                    if(vy == 0):
                        typ = 'RIVER_H';
                    else:
                        typ = 'RIVER_V';
                if(not (self.isValidPosition(px+vx, py+vy) and not self.data[px+vx][py+vy].isRiver())):
                    break;


class ClientThread(Thread):
    
    def __init__(self, pConnection):
        Thread.__init__(self);
        self.connection = pConnection;

    def send(self, pText):
        self.connection.sendall((pText + '~').encode('utf-8'));
        
    def run(self):
        global world;
        while True:
            data = self.connection.recv(32);
            print("Received command: " + str(data));
            command = data.decode('utf-8');
            args = command.split(" ");
            if(args[0] == 'MAP'):
                if(args[1] =='GET'):
                    #TILE X Y TYP ROTATION
                    for x in range(300):
                        for y in range(300):
                            self.send(world.data[x][y].getProtocolString());
                            

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

world = World();
world.generateWorld();


server = socket.socket(socket.AF_INET, socket.SOCK_STREAM);
server.bind( (CONFIG['bind_ip'], CONFIG['port']) );
server.listen();

clients = [];

print("Server wird gestartet...");
print(CONFIG);

try:
    while True:
        connection, address = server.accept();
        print("Verbindungsaufbau von " + str(address) + "...");
        thread = ClientThread(connection);
        thread.start();
        clients.append(thread);
                
except KeyboardInterrupt:
    print("Server beendet");






