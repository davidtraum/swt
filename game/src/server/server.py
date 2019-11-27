import json
import os
import socket
from threading import Thread
import time
import random
from RailClass import RailLogic


clients = []
def broadcast(pText, exclude=None):
    global clients
    for client in clients:
        try:
            if client != exclude:
                client.send(pText)
        except Exception:
            client.disconnect()


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
        'RAIL_RB': 14,
        'WATER': 15
    }

    def __init__(self, pX, pY, pType, pLogic=None):
        self.type = None
        self.rotation = 0
        self.x = pX
        self.y = pY
        self.setType(pType, share=False)
        self.logic = pLogic

    def getPos(self):
        return self.x, self.y

    def getX(self):
        return self.x

    def getY(self):
        return self.y

    def setType(self, pType, share=True):
        self.setRotation(0)
        self.type = MapTile.TYPES[pType]
        if(share):
            broadcast(self.getProtocolString())
            print("Kachel bei ", self.x, " ", self.y, " geändert. ", self.type);

    def getType(self):
        return self.type

    def setRotation(self, pRotation):
        self.rotation = pRotation

    def isRiver(self):
        return self.type >= 3 and self.type <= 8

    def isRail(self):
        return self.type >= 9 and self.type <= 11

    def getProtocolString(self):
        return 'TILE ' + str(self.x) + ' ' + str(self.y) + ' ' + str(self.type) + ' ' + str(self.rotation)

    def isInGroup(self, types):
        for type in types:
            if(self.type == MapTile.TYPES[type]):
                return True

    def logicUpdate(self):
        if(self.logic != None):
            print("MapTile @ LogicUpdate ", self.x, " " , self.y)
            newType = self.logic.getType()
            if(MapTile.TYPES[newType] != self.type):
                print("MapTile @ LogicChanged ", newType)
                self.setType(newType)

    def initLogic(self, pLogic):
        print("Init logic @ ", self.x, " ", self.y)
        self.logic = pLogic(self, None)
        self.logicUpdate()


class World:

    def __init__(self):
        self.data = []
        for x in  range(300):
            self.data.append([])
            for y in range(300):
                self.data[x].append(MapTile(x,y,'GRASS'))

    def randomPosition(self):
        return (random.randint(0, 299), random.randint(0, 299))

    def isValidPosition(self, posX, posY):
        return posX >= 0 and posY >= 0 and posX < 300 and posY < 300

    def canPlaceRail(self, posX, posY):
        return self.data[posX][posY].isInGroup(('GRASS', 'FOREST')) or True

    def tileInteract(self, posX, posY):
        print("Interact ", posX, " ", posY)
        if(self.canPlaceRail(posX, posY)):
            print("Placing rail...")
            RailLogic.build(posX, posY, None, self.data)
        else:
            print("Cant place rail " + str(self.data[posX][posY].getType()))

    def generateWorld(self):
        print("Welt wird generiert...")
        size = 300
        for x in range(size):
            for y in range(size):
                self.data[x][y].setRotation(random.randint(0, 3))
                if(random.randint(0, 100) < 20):
                    self.data[x][y].setType('FOREST')

        for townIndex in range(300):
            px, py = self.randomPosition()
            size = random.randint(3, 20)
            for houseIndex in range(size):
                self.data[px][py].setType('CITY')
                px += random.randint(-1, 1)
                py += random.randint(-1, 1)

                if(px < 0):
                    px = 0
                elif(px > 299):
                    px = 299

                if(py < 0):
                    py = 0
                elif(py > 299):
                    py = 299

        for riverIndex in range(20):
            px, py = self.randomPosition()
            vx = 1
            vy = 0
            sinceCurve = 0
            typ = 'RIVER_H'
            while True:
                self.data[px][py].setType(typ)
                self.data[px][py].setRotation(0)
                px += vx
                py += vy
                sinceCurve += 1
                if(sinceCurve > random.randint(3, 10)):
                    if(random.random() > 0.5):
                        if(vy == -1):
                            vy = 0
                            vx = 1
                            typ = 'RIVER_RB'
                        elif(vy == 0):
                            if(vx == -1):
                                typ = 'RIVER_RT'
                            else:
                                typ = 'RIVER_LT'
                            vy = -1
                            vx = 0
                        elif(vy == 1):
                            vy = 0
                            vx = -1
                            typ = 'RIVER_LT'
                    else:
                        if(vx == -1):
                            vy = 1
                            vx = 0
                            typ = 'RIVER_RB'
                        elif(vx == 0):
                            if(vy == 1):
                                typ = 'RIVER_LT'
                            else:
                                typ = 'RIVER_LB'
                            vy = 0
                            vx = -1
                        elif(vx == 1):
                            vy = -1
                            vx = 0
                            typ = 'RIVER_LT'
                    sinceCurve = 0
                else:
                    if(vy == 0):
                        typ = 'RIVER_H'
                    else:
                        typ = 'RIVER_V'
                if(not (self.isValidPosition(px+vx, py+vy) and not self.data[px+vx][py+vy].isRiver())):
                    break

        #Generierung von Meeren
        if False: #Setze True zum aktivieren
            for y in range(0, 40):
                minX = 40-y-3 
                if(minX < 0):
                    minX = 0 
                for x in range(random.randint(minX,40-y)):
                    self.data[x][y].setType('WATER') 
                for x in range(random.randint(minX,40-y)):
                    self.data[299-x][y].setType('WATER')  
            for y in range(150, 299):
                minX = 150-y-3 
                if(minX < 0):
                    minX = 0 
                for x in range(random.randint(minX,150-(y-150))):
                    self.data[x][y].setType('WATER') 
                for x in range(random.randint(minX,150-(y-150))):
                    self.data[299-x][y].setType('WATER')         
        self.data[150][150].setType('RAIL_H')
        self.data[150][150].initLogic(RailLogic)


class ClientThread(Thread):

    def __init__(self, pConnection):
        Thread.__init__(self)
        self.connection = pConnection
        self.commandBuffer = ""

    def send(self, pText):
        self.connection.sendall((pText + '~').encode('utf-8'))

    def disconnect(self):
        global clients
        if(self in clients):
            clients.remove(self)
        print("Disconnected Client")
        try:
            self.connection.close()
        except Exception:
            pass

    def processCommand(self,command):
            args = command.split(" ")
            if(args[0] == 'MAP'):
                if(args[1] == 'GET'):
                    # TILE X Y TYP ROTATION
                    for x in range(300):
                        time.sleep(0.001)
                        for y in range(300):
                            if(world.data[x][y].getType() > 0):
                                self.send(world.data[x][y].getProtocolString())
                    self.send("MAP DONE")
            elif(args[0] == 'BUILD'):
                if(args[1] == 'RAIL'):
                    print("Build Rail Request at ", args[2], " ", args[3])
                    posX = int(args[2])
                    posY = int(args[3])
                    world.tileInteract(posX, posY)
            elif(args[0] == 'POS'):
                print("got pos update " + command)
                posX = int(args[1])
                posY = int(args[2])
                broadcast("POS " + str(posX) + " " + str(posY), exclude=self)
            else:
                pass

    def run(self):
        global world
        overshoot = ""
        while True:
            try:
                data = self.connection.recv(1024)
                if(len(data)>0):
                    print(data.decode('utf-8'))
                    split = data.decode('utf-8').split("~")
                    length = len(split)
                    for cmd in split:
                        self.processCommand(cmd)
            except Exception as e:
                print(e)
                self.disconnect()
                break
            
            

DEFAULT_CONFIG = {
    'port': 2000,
    'bind_ip': 'localhost',
    'max_players': 5}

CONFIG_FILE = 'config.json'

if not os.path.exists(CONFIG_FILE):
    print("Die Konfigurationsdatei wird angelegt...")
    with open(CONFIG_FILE, 'w') as file:
        json_string = json.dumps(DEFAULT_CONFIG, indent=4)
        file.write(json_string)
        file.flush()


CONFIG = None
with open(CONFIG_FILE) as file:
    CONFIG = json.loads(file.read())

world = World()
world.generateWorld()


server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((CONFIG['bind_ip'], CONFIG['port']))
server.listen()


print("Server wird gestartet...")
print(CONFIG)


try:
    while True:
        connection, address = server.accept()
        print("Verbindungsaufbau von " + str(address) + "...")
        thread = ClientThread(connection)
        thread.start()
        clients.append(thread)

except KeyboardInterrupt:
    for client in clients:
        client.disconnect()
    print("Server beendet")

