import json
import os
import socket
from threading import Thread
import time
import random
from RailClass import RailLogic


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
        self.setType(pType, doBroadcast=False)
        self.logic = pLogic

    def getPos(self):
        return self.x, self.y

    def getX(self):
        return self.x

    def getY(self):
        return self.y

    def setType(self, pType, doBroadcast=True):
        self.setRotation(0)
        self.type = MapTile.TYPES[pType]
        if(doBroadcast):
            broadcast(self.getProtocolString())

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

    def initLogic(self, pLogic):
        self.logic = pLogic(self, None)


class World:

    def __init__(self):
        self.data = [[MapTile(j, i, 'GRASS')
                      for i in range(300)] for j in range(300)]

    def randomPosition(self):
        return (random.randint(0, 299), random.randint(0, 299))

    def isValidPosition(self, posX, posY):
        return posX >= 0 and posY >= 0 and posX < 300 and posY < 300

    def canPlaceRail(self, posX, posY):
        return self.data[posX][posY].isInGroup(('GRASS', 'FOREST'))

    def tileInteract(self, posX, posY):
        print("Interact ", posX, " ", posY)
        if(self.canPlaceRail(posX, posY)):
            print("Placing rail...")
            changed = RailLogic.build(posX, posY, None, self.data)
            if(changed != None):
                for tile in changed:
                    pass
        else:
            print("Cant place rail " + str(self.data[posX][posY].getType()))

    def generateWorld(self):
        print("Welt wird generiert...")
        size = 300
        for x in range(size):
            for y in range(size):
                self.data[x][y].setRotation(random.randint(0, 3))
                if(random.randint(0, 100) < 20):
                    self.data[x][y].setType('FOREST', doBroadcast=False)

        for townIndex in range(300):
            px, py = self.randomPosition()
            size = random.randint(3, 20)
            for houseIndex in range(size):
                self.data[px][py].setType('CITY', doBroadcast=False)
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
                self.data[px][py].setType(typ, doBroadcast=False)
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
                            typ = 'RIVER_LB'
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
                    self.data[x][y].setType('WATER', doBroadcast=False) 
                for x in range(random.randint(minX,40-y)):
                    self.data[299-x][y].setType('WATER', doBroadcast=False)  
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

    def send(self, pText):
        self.connection.sendall((pText + '~').encode('utf-8'))

    def run(self):
        global world
        while True:
            data = self.connection.recv(32)
            print("Received command: " + str(data))
            command = data.decode('utf-8')
            args = command.split(" ")
            if(args[0] == 'MAP'):
                if(args[1] == 'GET'):
                    # TILE X Y TYP ROTATION
                    for x in range(300):
                        for y in range(300):
                            self.send(world.data[x][y].getProtocolString())
            elif(args[0] == 'TILE'):
                if(args[1] == 'CLICK'):
                    print("Setting tile...")
                    posX = int(args[2])
                    posY = int(args[3])
                    world.tileInteract(posX, posY)


if __name__ == '__main__':
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

    clients = []

    print("Server wird gestartet...")
    print(CONFIG)


    def broadcast(pText):
        global clients
        for client in clients:
            client.send(pText)


    try:
        while True:
            connection, address = server.accept()
            print("Verbindungsaufbau von " + str(address) + "...")
            thread = ClientThread(connection)
            thread.start()
            clients.append(thread)

    except KeyboardInterrupt:
        print("Server beendet")
