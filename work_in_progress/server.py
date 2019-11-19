from RailClass import *
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
        'RAIL_H': 9,
        'RAIL_V': 10,
        'RAIL_LB': 11,
        'RAIL_LT': 12,
        'RAIL_RT': 13,
        'RAIL_RB': 14
        
    }
    
    def __init__(self, pX, pY, pType):
        self.type = None;
        self.rotation = 0;
        self.x = pX;
        self.y = pY;
        self.setType(pType);

    def setType(self, pType):
        self.type = MapTile.TYPES[pType];

    def getType(self):
        return self.type;

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

    #--------Gleis-Logik
    def checkRailSurroundings(self, px, py):
        self.railExistsUp, self.railExistsDown, self.railExistsRight, self.railExistsLeft = RailLogic._checkRails(self, px, py, self.data);

    def setRail(self, px, py, rail):
        self.railPlaced(px, py); 
        if (railExistsUp + railExistsDown + railExistsRight + railExistsLeft == 0):
            pass; #Hier Fehlerausgabe einfügen, denn jede Schiene muss an mindestens eine andere Schiene gebaut werden (wie in Original)
        
        #M
        if (railExistsUp + railExistsDown + railExistsRight + railExistsLeft == 1):
            #wenn nur eine andere Schiene braucht es maximal eine Kurve/max. 1 Maptile muss verändert werden
            if (railExistsRight != 0 and self.direction == 0):  #keine Kurve
                pass;
            if (railExistsRight != 0  and self.direction == 1):  #rightUp
                curve = CurveLogic
                CurveLogic.curvedirection = CurveDirection.rightUp
                self.data[px-1][py] = curve
            if (railExistsLeft != 0 and self.direction == 0):  #keine Kurve
                pass;
            if (railExistsLeft != 0 and self.direction == 1):  #LeftUp
                curve = CurveLogic
                CurveLogic.curvedirection = CurveDirection.LeftUp
                self.data[px+1][py] = curve
            if (railExistsRight == 1 and self.direction == 0):  #
                curve = CurveLogic
                CurveLogic.curvedirection = CurveDirection.UpRight
                self.data[px-1][py] = curve

        #J
        if (railExistsUp + railExistsDown + railExistsRight + railExistsLeft == 2):
            if (railExiststRight == 9 and railExistsLeft == 9):
                RailLogic(world,px,py,"RAIL_H");
            if (railExiststRight == 9 and railExistsLeft == 10):
                pass; #Bauen nicht möglich
            if (railExiststRight == 9 and railExistsLeft == 11):
                RailLogic(world,px,py,"RAIL_H");
            if (railExiststRight == 9 and railExistsLeft == 12):
                RailLogic(world,px,py,"RAIL_H");
            if (railExiststRight == 9 and railExistsLeft == 13):
                pass; #Bauen nicht möglich
            if (railExiststRight == 9 and railExistsLeft == 14):
                pass; #Bauen nicht möglich
            if (railExiststRight == 10 and railExistsLeft == 11):
                RailLogic(world,px,py,"RAIL_H");
            if (railExiststRight == 10 and railExistsLeft == 12):
                RailLogic(world,px,py,"RAIL_H");
            if (railExiststRight == 10 and railExistsLeft == 13):
                RailLogic(world,px,py,"RAIL_H");
            if (railExiststRight == 10 and railExistsLeft == 14):
                RailLogic(world,px,py,"RAIL_H");
            if (railExiststRight == 11 and railExistsLeft == 12):
                RailLogic(world,px,py,"RAIL_H");
            if (railExiststRight == 11 and railExistsLeft == 13):
                RailLogic(world,px,py,"RAIL_H");
            if (railExiststRight == 11 and railExistsLeft == 14):
                RailLogic(world,px,py,"RAIL_H");
            if (railExiststRight == 12 and railExistsLeft == 13):
                RailLogic(world,px,py,"RAIL_H");
            if (railExiststRight == 12 and railExistsLeft == 14):
                RailLogic(world,px,py,"RAIL_H");
            if (railExiststRight == 13 and railExistsLeft == 14):
                RailLogic(world,px,py,"RAIL_H");
            
    #-------------------
                
                
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
#------------------------------------Testbereich Gleise

rail1 = RailLogic(world,5,9,"RAIL_RB");
world.railExistsUp, world.railExistsDown, world.railExistsRight, world.railExistsLeft = RailLogic._checkRails(world, 5, 8, world.data);
print(world.railExistsUp);
print(world.railExistsDown);
print(world.railExistsRight);
print(world.railExistsLeft);

#------------------------------------------------------

try:
    while True:
        connection, address = server.accept();
        print("Verbindungsaufbau von " + str(address) + "...");
        thread = ClientThread(connection);
        thread.start();
        clients.append(thread);
                
except KeyboardInterrupt:
    print("Server beendet");

