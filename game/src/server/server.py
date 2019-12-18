import json
import os
import socket
from threading import Thread
import time
import random
from RailClass import RailLogic
from TrainStationClass import TrainStationLogic
from PlayerClass import Player
from BridgeClass import BridgeLogic
from WayClass import WayLogic


clients = []
clientCount = 0
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
        'WATER': 15,
        'DEPOT_H': 16,
        'DEPOT_V':  17,
        'STATION_H' : 18,
        'STATION_V' : 19,
        'TERMINAL_H' : 20,
        'TERMINAL_V' : 21,
        'BRIDGE_H': 22,
        'BRIDGE_V': 23
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

    def setType(self, pType, share=True, resetRotation=True):
        if(resetRotation):
            self.setRotation(0)
        self.type = MapTile.TYPES[pType]
        if(share):
            broadcast(self.getProtocolString())
            print("Kachel bei ", self.x, " ", self.y, " geändert. ", self.type)

    def getType(self):
        return self.type

    def setRotation(self, pRotation):
        self.rotation = pRotation

    def rotateClockwise(self, share=True):
        self.rotation+=1
        if(self.rotation>3):
            self.rotation=0
        if(share):
            broadcast(self.getProtocolString())


    def isRiver(self):
        return self.type >= 3 and self.type <= 8

    def isRail(self):
        return self.type >= 9 and self.type <= 14 or self.type == 22 or self.type == 23

    def isTrainStation(self):
        return self.type >= 16 and self.type <= 21

    def checkRotationStationVertical(self):
        return self.type == 17 or self.type == 19 or self.type == 21

    def getProtocolString(self):
        #print('der gesendete Typ ist:')
        #print(self.type)
        return 'TILE+' + str(self.x) + '+' + str(self.y) + '+' + str(self.type) + '+' + str(self.rotation)

    def isInGroup(self, types):
        for type in types:
            if(self.type == MapTile.TYPES[type]):
                return True

    def logicUpdate(self):
        if(self.logic != None):
            print("MapTile @ LogicUpdate ", self.x, " " , self.y)
            newType = self.logic.getType()
            print(self.type, newType)
            if(MapTile.TYPES[newType] != self.type):
                print("MapTile @ LogicChanged ", newType)
                self.setType(newType)

    def initLogic(self, pLogic, pRange = 0):
        print("Init logic @ ", self.x, " ", self.y)
        if(pLogic == RailLogic or pLogic == BridgeLogic):
            self.logic = pLogic(self, None)
        if(pLogic == TrainStationLogic):
            self.logic = pLogic(self, None, pRange, 2)
        


class World:

    def __init__(self):
        self.data = []
        self.startTime = int(time.time() * 1000)
        for x in  range(300):
            self.data.append([])
            for y in range(300):
                self.data[x].append(MapTile(x,y,'GRASS'))

    def randomPosition(self):
        return (random.randint(0, 299), random.randint(0, 299))

    def isValidPosition(self, posX, posY):
        return posX >= 0 and posY >= 0 and posX < 300 and posY < 300

    def canPlaceObject(self, posX, posY):       
        return self.data[posX][posY].isInGroup(('GRASS', 'FOREST')) or False

        
    def canPlaceRailOnRiver(self, posX, posY):
        return self.data[posX][posY].isInGroup(('RIVER_H', 'RIVER_V')) or False

    def getGametime(self):
        currentTime = int(time.time()*1000)
        diff = currentTime - self.startTime
        return int(diff/20)

    def tileInteract(self, posX, posY, pType):
        print("Interact ", posX, " ", posY, " ", pType)
        if(pType == 'RAIL' and self.canPlaceObject(posX, posY)):
            print("Placing rail...")
            RailLogic.build(posX, posY, None, self.data)
        elif(pType == 'RAIL' and self.canPlaceRailOnRiver(posX, posY)):
            print("Placing bridge...")
            BridgeLogic.build(posX, posY, None, self.data, self.data[posX][posY].getType())
        elif(pType == 'DEPOT' and self.canPlaceObject):
            print("Placing depot...")
            TrainStationLogic.build(posX, posY, None, 2, self.data)
        elif(pType == 'STATION' and self.canPlaceObject):
            print("Placing station...")
            TrainStationLogic.build(posX, posY, None, 4, self.data)
        elif(pType == 'TERMINAL' and self.canPlaceObject):
            print("Placing terminal...")
            TrainStationLogic.build(posX, posY, None, 6, self.data)
        else:
            print("Cant place rail " + str(self.data[posX][posY].getType()))

    def tileRightclick(self, posX, posY):
        if(self.data[posX][posY].isRail()):
            self.data[posX][posY].rotateClockwise()
        else:
            self.data[posX][posY].setType('GRASS')
        self.data[posX][posY]

    def generateWorld(self):
        print("Welt wird generiert...")
        size = 300
        for x in range(size):
            for y in range(size):
                if(random.randint(0, 100) < 20):
                    self.data[x][y].setType('FOREST')
                self.data[x][y].setRotation(random.randint(0, 3))

        for townIndex in range(300):
            px, py = self.randomPosition()
            size = random.randint(3, 20)
            for houseIndex in range(size):
                self.data[px][py].setType('CITY', resetRotation=False)
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

        self.data[150][150].initLogic(RailLogic)
        self.data[150][150].logicUpdate()
        WayLogic.allWays.append(WayLogic(None))
        WayLogic.allWays[0].firstRail.append(self.data[150][150])
        WayLogic.allWays[0].secondRail.append(None)
        self.data[150][150].logic.way = WayLogic.allWays[0]
        world.tileInteract(149, 150, 'DEPOT')
        world.tileInteract(148, 150, 'RAIL')
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


class ClientThread(Thread):

    def __init__(self, pConnection):
        Thread.__init__(self)
        self.connection = pConnection
        self.commandBuffer = ""
        print("CLIENT THREAD WIRD GESTARTET");
        time.sleep(3);
        self.player = Player(clientCount, 1234); #"1234" muss durch IP ersetzt werden.
        print("Client Thread gestartet.");
        time.sleep(3);

    def send(self, pText):
        self.connection.sendall(('CMD+' + pText + '~').encode())

    def disconnect(self):
        global clients
        if(self in clients):
            clients.remove(self)
        print("Disconnected Client")
        try:
            self.connection.close()
            clientCount -= 1;
            del self.player;
            print("Anzahl verbundener Clients: " + clientCount);
        except Exception:
            print("FEHLER BEIM DISCONNECT");

    def processCommand(self,command):
            global world
            print(command)
            args = command.split(" ")
            if(args[0] == 'MAP'):
                if(args[1] == 'GET'):
                    # TILE X Y TYP ROTATION
                    for x in range(300):
                        time.sleep(0.002)
                        for y in range(300):
                            if(world.data[x][y].getType() > 0):
                                self.send(world.data[x][y].getProtocolString())
                    self.send("MAP+DONE")
                    self.send("TIME+" + str(world.getGametime()))
            elif(args[0] == 'BUILD'):
                posX = int(args[2])
                posY = int(args[3])
                if(args[1] == 'RAIL'):
                    print("Build Rail Request at ", args[2], " ", args[3])
                    #world.data[posX][posY].setType('RAIL_H')
                    world.tileInteract(posX, posY, 'RAIL')
                elif(args[1] == 'STATION'):                    
                    print("Build Trainstation Request at ", args[2], " ", args[3])
                    if(args[4] == 'DEPOT'):    
                        world.tileInteract(posX, posY, 'DEPOT')
                        print("Build Depot Request at ", args[2], " ", args[3])
                    if(args[4] == 'STATION'):    
                        world.tileInteract(posX, posY, 'STATION')
                        print("Build Station Request at ", args[2], " ", args[3])
                    if(args[4] == 'TERMINAL'):    
                        world.tileInteract(posX, posY, 'TERMINAL')
                        print("Build Terminal Request at ", args[2], " ", args[3])
                if(args[1] == 'INTERACT'):
                    print("Build interact")
                    world.tileRightclick(posX, posY)
            elif(args[0] == 'POS'):
                print("got pos update " + command)
                posX = int(args[1])
                posY = int(args[2])
                broadcast("POS+" + str(posX) + "+" + str(posY), exclude=self)
            else:
                print(command)

    def run(self):
        global world
        buffer = b""
        while True:
            try:
                data = self.connection.recv(1)
                if(data == b'~'):
                    self.processCommand(buffer.decode())
                    buffer = b""
                else:
                    buffer += data
            except Exception as e:
                print(e)
                self.disconnect()
                break
            
            

DEFAULT_CONFIG = {
    'port': 2000,
    'bind_ip': 'localhost',
    'max_players': 5}

CONFIG_FILE = 'config.json'

#Config-Datei
if not os.path.exists(CONFIG_FILE):
    print("Die Konfigurationsdatei wird angelegt...")
    with open(CONFIG_FILE, 'w') as file:
        json_string = json.dumps(DEFAULT_CONFIG, indent=4)
        file.write(json_string)
        file.flush()


CONFIG = None
with open(CONFIG_FILE) as file:
    CONFIG = json.loads(file.read())
#Ende Config-Datei

#Weltgenerierung    
world = World()
world.generateWorld()

#Spieler Daten (Guthaben, usw.), aktuell ausgelegt für bis zu 4 Spielerkonten
DEFAULT_PLAYERDATA = {
    'p1_id': 0,
    'p1_money': 1000,
    'p2_id': 0,
    'p2_money': 1000,
    'p3_id': 0,
    'p3_money': 1000,
    'p4_id': 0,
    'p4_money': 1000}

PLAYER_DATA = 'playerData.json'

if not os.path.exists(PLAYER_DATA):
    print("Die Spielerdaten-Datei wird angelegt...")
    with open(PLAYER_DATA, 'w') as file:
        json_string = json.dumps(DEFAULT_PLAYERDATA, indent=4)
        file.write(json_string)
        file.flush()
#Ende Spielerdaten-Abschnitt

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((CONFIG['bind_ip'], CONFIG['port']))
server.listen()


print("Server wird gestartet...")
print(CONFIG)


try:
    while True:
        connection, address = server.accept()
        print("Verbindungsaufbau von " + str(address) + "...")
        clientCount += 1;
        thread = ClientThread(connection)
        thread.start()
        clients.append(thread)
        print("Anzahl verbundener Clients: " + str(clientCount));
        
        
except KeyboardInterrupt:
    for client in clients:
        client.disconnect()
    print("Server beendet")
