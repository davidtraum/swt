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
from RouteClass import RouteLogic


clients = []
clientCount = 0
tasks = []

#Ein Broadcast geht an alle verbundenen Clients raus
def broadcast(pText, exclude=None):     
    global clients
    for client in clients:
        try:
            if client != exclude:
                client.send(pText)
        except Exception:
            client.disconnect()

#Die Klasse MapTile dient zur Bestimmung des Typs der Kacheln auf der Karte
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
        'BRIDGE_V': 23,
        'CORN': 24,
        'COAL': 25, 
        'WOOD': 26,
        'FOOD': 27,
        'LIVESTOCK': 28,
        'GOODS': 29,
        'PETROLEUM': 30,
        'PAPER': 31,
        'STEEL': 32
        
 
                
    }

    def __init__(self, pX, pY, pType, pLogic=None):
        self.type = None
        self.rotation = 0
        self.x = pX
        self.y = pY
        self.setType(pType, share=False)
        self.logic = pLogic
        
    #Gibt die Position des MapTiles zurück
    def getPos(self):
        return self.x, self.y

    #Gibt die x-Koordinate des MapTiles zurück
    def getX(self):
        return self.x

    #Gibt die y-Koordinate des MapTiles zurück
    def getY(self):
        return self.y

    #Setzt den Typ der Kachel auf den Typ pType
    def setType(self, pType, share=True, resetRotation=True):
        if(resetRotation):
            self.setRotation(0)
        self.type = MapTile.TYPES[pType]
        if(share):
            broadcast(self.getProtocolString())
            #print("Kachel bei ", self.x, " ", self.y, " geändert. ", self.type)

    #Gibt den Typ der Kachel zurück
    def getType(self):        
        return self.type

    #Gibt den Typ der Kachel als String zurück
    def getStringType(self):
        for key in MapTile.TYPES:
            if(MapTile.TYPES[key]==self.type):
                return key
        
    #Setzt die Rotation der Kachel
    def setRotation(self, pRotation):
        self.rotation = pRotation

    #Das MapTile wird einmal im Uhrzeigersinn gedreht
    def rotateClockwise(self, share=True):
        self.rotation+=1
        if(self.rotation>3):
            self.rotation=0
        if(share):
            broadcast(self.getProtocolString())

    #Liefert true zurück, wenn das MapTile ein Fluss ist
    def isRiver(self):
        return self.type >= 3 and self.type <= 8

    #Liefert true zurück, wenn das MapTile eine Schiene ist
    def isRail(self):
        return self.type >= 9 and self.type <= 14 or self.type == 22 or self.type == 23
    
    #Liefert true zurück, wenn das MapTile ein Bahnhof ist
    def isTrainStation(self):
        return self.type >= 16 and self.type <= 21
    
    #Liefert true zurück, wenn das MapTile eine Erzeugungsstatte ist
    def isProducingBuilding(self):
        return self.type >= 24 and self.type <= 32 or self.type == 2

    #Gibt True zurück, wenn an der Stelle ein vertikaler Bahnhof ist
    def checkRotationStationVertical(self):
        return self.type == 17 or self.type == 19 or self.type == 21

    #Gibt einen an den Client verschickbaren String zurück, der die Eigenschaften des MapTiles beinhaltet
    def getProtocolString(self):
        return 'TILE+' + str(self.x) + '+' + str(self.y) + '+' + str(self.type) + '+' + str(self.rotation)

    #Gibt true zurück, wenn der übergebene Typ mit der Gruppe übereinstimmt
    def isInGroup(self, types):
        for type in types:
            if(self.type == MapTile.TYPES[type]):
                return True

    #Wird aufgerufen, wenn sich die Logik des MapTiles ändert (wenn z.B. eine Schiene platziert wird)
    def logicUpdate(self):
        if(self.logic != None):
            print("MapTile @ LogicUpdate ", self.x, " " , self.y)            
            newType = self.logic.getType()
            print(self.type, newType)            
            if(MapTile.TYPES[newType] != self.type):
                print("MapTile @ LogicChanged ", newType)
                self.setType(newType)

    #Initialisiert Logikelemente des entsprechenden Kacheltyps, wenn diese auf der Karte platziert werden
    def initLogic(self, pLogic, karte = None, pRange = 2):
        print("Init logic @ ", self.x, " ", self.y)
        if(pLogic == RailLogic or pLogic == BridgeLogic):
            self.logic = pLogic(self, None)
        if(pLogic == TrainStationLogic):
            self.logic = pLogic(self, None, pRange, 2, karte)
            tasks.append(self.logic)
        

#Diese Klasse beinhaltet die Karteninformationen (Jede Kachel steht für ein MapTile)
class World:

    def __init__(self):
        self.data = []
        self.startTime = int(time.time() * 1000)
        for x in  range(300):
            self.data.append([])
            for y in range(300):
                self.data[x].append(MapTile(x,y,'GRASS'))

    #Gibt eine zufällige x-y-Position auf der Karte zurück
    def randomPosition(self):
        return (random.randint(0, 299), random.randint(0, 299))

    #Prüft ob die übergebenen Koordinaten eine gültige Position sind, also nicht außerhalb der generierten Karte vorliegen
    def isValidPosition(self, posX, posY):
        return posX >= 0 and posY >= 0 and posX < 300 and posY < 300

    #Gibt true zurück, wenn man bei den übergebenen Koordinaten x,y bauen darf. Es darf nur auf Wald und Wiese gebaut werden.
    def canPlaceObject(self, posX, posY):       
        return self.data[posX][posY].isInGroup(('GRASS', 'FOREST')) or False

    #Prüft ob an der übergebenen Position eine Schiene/Brücke auf den Fluss gebaut werden kann    
    def canPlaceRailOnRiver(self, posX, posY):
        return self.data[posX][posY].isInGroup(('RIVER_H', 'RIVER_V')) or False

    #Gibt die Spielzeit zurück
    def getGametime(self):
        currentTime = int(time.time()*1000)
        diff = currentTime - self.startTime
        return int(diff/20)
    
    #Funktion zur Unterscheidung welche Interaktion mit einem MapTile durchgeführt wurde.
    def tileInteract(self, posX, posY, pType):  
        print("Interact ", posX, " ", posY, " ", pType)
        if(pType == 'RAIL' and self.canPlaceObject(posX, posY)):
            print("Placing rail...")
            return RailLogic.build(posX, posY, None, self.data)
        elif(pType == 'RAIL' and self.canPlaceRailOnRiver(posX, posY)):
            print("Placing bridge...")
            return BridgeLogic.build(posX, posY, None, self.data, self.data[posX][posY].getType())
        elif(pType == 'DEPOT' and self.canPlaceObject):
            print("Placing depot...")
            return TrainStationLogic.build(posX, posY, None, 2, self.data)
        elif(pType == 'STATION' and self.canPlaceObject):
            print("Placing station...")
            return TrainStationLogic.build(posX, posY, None, 4, self.data)
        elif(pType == 'TERMINAL' and self.canPlaceObject):
            print("Placing terminal...")
            return TrainStationLogic.build(posX, posY, None, 6, self.data)
        else:
            print("Cant place rail " + str(self.data[posX][posY].getType()))
            return False

    #Entfernt ein Maptile (wird zu Flachland/Gras)
    def tileRemove(self, posX, posY):  
        if(self.data[posX][posY].type >= 9 and self.data[posX][posY].type <= 14):
            print("Remove Rail Request at ", posX, " ", posY)
            self.data[posX][posY].logic.remove(posX, posY, None, self.data)

    def tileRightclick(self, posX, posY):
        if(self.data[posX][posY].isRail()):
            self.data[posX][posY].rotateClockwise()
        else:
            self.data[posX][posY].setType('GRASS')
        #self.data[posX][posY]

    #Weltgenerierung nach Start des Servers
    def generateWorld(self):    
        print("Welt wird generiert...")
        size = 300
        for x in range(size):
            for y in range(size):
                if(random.randint(0, 100) < 20):
                    self.data[x][y].setType('FOREST')
                self.data[x][y].setRotation(random.randint(0, 3))

                for z in range(24,32):
                         for key in MapTile.TYPES:
                             if(MapTile.TYPES[key] == z):
                                 if(random.randint(0, 100) < 0.005):
                                    self.data[x][y].setType(key)
                if(random.randint(0, 100) < 0.25):
                     self.data[x][y].setType('COAL')

        for townIndex in range(300):    #generiere Städte
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

        for riverIndex in range(20):    #generiere Flüsse
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
                
        testStrecke = True
        Richtung = "rechts"                
        if(testStrecke == True):    #generiert Teststrecke
            testTrainstations = []
            if(Richtung == 'links'):
                self.data[150][150].initLogic(TrainStationLogic, self.data)
                self.data[150][150].type = 16
                testTrainstations.append(self.data[150][150])
                #print(self.data[150][150].getType())         
                for i in range(0,10):
                    if(i != 9):
                        world.tileInteract(149-i, 150, 'RAIL')
                    else:
                        world.tileInteract(149-i, 150, 'TERMINAL')
                        testTrainstations.append(self.data[149-i][150])                        
            elif(Richtung == 'rechts'):
                self.data[150][150].initLogic(TrainStationLogic, self.data)
                self.data[150][150].type = 16
                testTrainstations.append(self.data[150][150].logic)
                print(self.data[150][150].getType())         
                for i in range(0,10):
                    if(i != 9):
                        world.tileInteract(149+i, 150, 'RAIL')
                    else:                   
                        world.tileInteract(149+i, 150, 'TERMINAL')
                        testTrainstations.append(self.data[149+i][150])                       
            elif(Richtung == 'oben'):
                self.data[150][150].initLogic(TrainStationLogic, self.data)
                self.data[150][150].type = 17
                testTrainstations.append(self.data[150][150].logic)
                print(self.data[150][150].getType())         
                for i in range(0,10):
                    if(i != 9):
                        world.tileInteract(150, 149-1, 'RAIL')
                    else:                    
                        world.tileInteract(150, 149-1, 'TERMINAL')
                        testTrainstations.append(self.data[150][149-i])                       
            elif(Richtung == 'unten'):
                self.data[150][150].initLogic(TrainStationLogic, self.data)
                self.data[150][150].type = 17
                testTrainstations.append(self.data[150][150].logic)
                print(self.data[150][150].getType())         
                for i in range(0,10):
                    if(i != 9):
                        world.tileInteract(150, 149+i, 'RAIL')
                    else:
                        world.tileInteract(150, 149+i, 'TERMINAL') 
                        testTrainstations.append(self.data[150][149+i])          
            testWagons=[]
            for j in range(7):
                testWagons.append("CORN")
            
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

                     
#GameLoop lässt die Zeit im Spiel weiterlaufen
class GameLoopThread(Thread):  

    def __init__(self, tickspeed=20):
        Thread.__init__(self)
        self.tickspeed = tickspeed/1000.0
        self.last_mach_was = 0
        self.running = False

    def do_loop(self):
        for task in tasks:
            task.do_loop()

    def run(self):
        self.running = True
        while self.running:
            self.do_loop()
            time.sleep(self.tickspeed)


#Jeder Client erhält seinen eigenen Thread
class ClientThread(Thread):     

    def __init__(self, pConnection):
        Thread.__init__(self)
        self.connection = pConnection
        self.commandBuffer = ""
        print("CLIENT THREAD WIRD GESTARTET")
        self.player = Player(1234, tasks, world.data, CONFIG['game']['defaultmoney']) #"1234" muss durch IP ersetzt werden.
        print("Client Thread gestartet.")

    #Sendet den Text pText als Befehl an den Client. Befehlteile werden mit "+" voneinander getrennt
    def send(self, pText):
        self.connection.send(bytes([0,0,0,0,255, len(pText)]))
        self.connection.sendall(pText.encode())
        #print("An Client gesendet: " + 'CMD+' + pText + '~')    #Testausgabe

    def syncMoney(self):
        self.send("MONEY+" + str(self.player.money))

    #Zwingt den Client sich mit dem Server zu synchronisieren
    def forceSync(self):
        self.send("SYNC")

    #Disconnectet einen Client
    def disconnect(self):   
        global clients
        global clientCount
        if(self in clients):
            clients.remove(self)
        print("Disconnected Client")
        try:
            self.connection.close()
            clientCount -= 1
            del self.player
            print("Anzahl verbundener Clients: " + clientCount)
        except Exception:
            print("FEHLER BEIM DISCONNECT")

    #Befehlsverarbeitung (Befehle des Client). Unterschiedliche Befehle lösen unterschiedliche Routinen aus.
    def processCommand(self,command):   
            global world
            print(command)
            args = command.split(" ")   #Der Server versteht Befehle mit " " Leerzeichen als Trennung

            #Befehlsverarbeitung MAP
            if(args[0] == 'MAP'):   
                if(args[1] == 'GET'):
                    # TILE X Y TYP ROTATION
                    for x in range(300):
                        for y in range(300):
                            if(world.data[x][y].getType() > 0):
                                #time.sleep(0.0001)
                                self.send(world.data[x][y].getProtocolString())
                    self.send("MAP+DONE")
                    self.send("TIME+" + str(world.getGametime()))
                    self.forceSync()

            #Befehlsverarbeitung BUILD
            elif(args[0] == 'BUILD'):   
                posX = int(args[2])
                posY = int(args[3])
                if(args[1] == 'RAIL'):
                    print("Build Rail Request at ", args[2], " ", args[3])
                    #world.data[posX][posY].setType('RAIL_H')
                    if(self.player.hasMoney(CONFIG['game']['prices']['bridge'])):
                        if(world.tileInteract(posX, posY, 'RAIL')):
                            self.player.money -= CONFIG['game']['prices']['bridge']
                            self.syncMoney()
                elif(args[1] == 'STATION'):                    
                    print("Build Trainstation Request at ", args[2], " ", args[3])
                    if(args[4] == 'DEPOT'):    
                        if(self.player.hasMoney(CONFIG['game']['prices']['depot'])):
                            if(world.tileInteract(posX, posY, 'DEPOT')):
                                self.player.money -= CONFIG['game']['prices']['depot']
                                self.syncMoney()
                    if(args[4] == 'STATION'):    
                        if(self.player.hasMoney(CONFIG['game']['prices']['station'])):
                            if(world.tileInteract(posX, posY, 'STATION')):
                                self.player.money -= CONFIG['game']['prices']['station']
                                self.syncMoney()
                        print("Build Station Request at ", args[2], " ", args[3])
                    if(args[4] == 'TERMINAL'):    
                        if(self.player.hasMoney(CONFIG['game']['prices']['terminal'])):
                            if(world.tileInteract(posX, posY, 'TERMINAL')):
                                self.player.money -= CONFIG['game']['prices']['terminal']
                                self.syncMoney()
                        print("Build Terminal Request at ", args[2], " ", args[3])
                if(args[1] == 'INTERACT'):
                    print("Build interact")
                    world.tileRightclick(posX, posY)
            elif(args[0] == 'WAY'):
                if(args[1] == 'GET'):
                    broadcast(WayLogic.getProtocolString())
            elif(args[0] == 'TRAINSTATION'):
                if(args[1] == 'GET'):
                    broadcast(WayLogic.getTrainstationProtocolString(int(args[2]),int(args[3]),world.data))
            elif(args[0] == 'CURVES'):  #gibt Eckpunkte
                if(args[1] == 'GET'):
                    broadcast(WayLogic.getCurves(world.data, args[2], args[3], args[4], args[5]))
            elif(args[0] == 'REMOVE'):  #Befehlsverarbeitung REMOVE
                posX = int(args[1])
                posY = int(args[2])
                world.tileRemove(posX, posY)
            elif(args[0] == 'INFO'):
                if(args[1] == 'GET'):                    
                    broadcast(world.data[int(args[2])][int(args[3])].logic.getProtocolStringStorage())
                    broadcast(world.data[int(args[2])][int(args[3])].logic.getProtocolStringPrices())
            #Befehlsverarbeitung ROUTE
            elif(args[0] == 'ROUTE'):   
                tsStops = [[]]     #speichert Koordinaten der Haltestellen auf der Route
                wagonTypes = []
                i=0    #Damit Array in Schleife bei 0 beginnt
                
                if(args[1] == "TS"):    #Client schickt Route mit Zwischenstops
                    i = i-2
                    
                    while True:
                        if(args[i+3] == "TS"):
                            i = i+3
                            tsStops.append([args[i+1],args[i+2]])      #Speichert Koordinaten in tsStops
                            print("Bin in TS Schleife ", i)
                        elif(args[i+3]== "WAGONS"):
                            print("Springe in Wagong rein ", i)
                            print("i ist ", i)
                            for j in range(i+4,len(args)):
                                if (args[j] == "COAL" or args[j] == "CORN" or args[j] == "PASSENGERS" or args[j] == "LIVESTOCK" or args[j] == "WOOD" or args[j] == "MAIL" or args[j] == "FOOD" or args[j] == "GOODS" or args[j] == "PAPER" or args[j] == "STEEL" or args[j] == "PETROLEUM"):
                                    wagonTypes.append(args[j])
                                else:
                                    routeName = args[j] 
                                print("Bin in Wagons Schleife ", j)
                            break
                    
                    tsStops.pop(0)     #Lösche erstes Listenelement, da immer leer
                    print("Routen-Befehl gespeichert: ")    
                    print("TS Coords: ")
                    print(*tsStops, sep='_', end='\n')
                    print("Wagon Types: ")
                    print(*wagonTypes, sep='_', end='\n')

                    handOver = self.player.addRoute(routeName, tsStops, wagonTypes)
                    broadcast("ROUTE+PLAY+" + handOver)

                elif(args[1] == "GET"):     #Client verlangt nach einer Liste mit allen ihm zugehörigen Routen
                    handOver = str(self.player.routes)
                    handOver = handOver.replace(",", "+")
                    handOver = handOver.replace("[", "")
                    handOver = handOver.replace("]", "")
                    handOver = handOver.replace(" ", "")
                    handOver = handOver.replace("'", "")             
                    print("HandOver ganzer String:" + handOver)
                    
                    handOverList = handOver.split("+")
                    wagonsWritten = False
                    coordsWritten = False
                    nameWritten = False
                    handOver = ""

                    #Schickt die Routen des Spielers einzeln als Strings an den Client
                    for i in range(0, len(handOverList)):
                        if ( handOverList[i] == "COAL" or handOverList[i] == "PETROLEUM" or handOverList[i] == "FOOD" or handOverList[i] == "LIVESTOCK" or handOverList[i] == "WOOD" or handOverList[i] == "CORN" or handOverList[i] == "GOODS" or handOverList[i] == "PAPER" or handOverList[i] == "MAIL" or handOverList[i] == "PASSENGERS" or handOverList[i] == "STEEL"):
                            wagonsWritten = True
                            coordsWritten = False
                            print("WAGGON GEFUNDEN")
                        elif (wagonsWritten or i == len(handOverList)):
                            coordsWritten = True
                            wagonsWritten = False
                            print("HandOver in Schleife: " + handOver)
                            self.send("ROUTES+" + handOver)
                            handOver = ""
                        else:
                            print("KEIN WAGGON, aber auch kein ENDE")
                        handOver += handOverList[i] + "+"
                        print("Schleifendurchlauf " + str(i) + "   " + handOver)
                    self.send("ROUTES+" + handOver) #Letzte Route auch senden
                        
                elif(args[1] == "DELETE"):
                    deletedID = self.player.cancelRoute(args[2])
                    print("ROUTE+DELETE+" + str(deletedID))
                    broadcast("ROUTE+DELETE+" + str(deletedID))
                    
                elif(args[1] == "PASS"):
                    routeTmp = None
                    routeExistiert = 0
                    print('Länge RoutenObjekt:', len(self.player.routeObjectList))
                    for i in range(len(self.player.routeObjectList)):
                        print(self.player.routeObjectList[i].id,  args[2])
                        if(self.player.routeObjectList[i].id == int(args[2])):
                            routeExistiert = 1
                    if(routeExistiert == 1):
                        print("Route: Zug nr. ", args[2], "hat den Bahnhof bei", args[3], "/", args[4], "passiert.")
                        for i in range(len(self.player.routeObjectList)):
                            if(self.player.routeObjectList[i].id == int(args[2])):
                                routeTmp = self.player.routeObjectList[i]
                        if(len(routeTmp.train.wagons) != 0):
                            routeTmp.train.removeWagons(world.data[int(args[3])][int(args[4])])
                            self.syncMoney()                                                                     
                        print("vor addWagons")
                        print(routeTmp.lenStationList)
                        if(routeTmp.stationCounter +1 <= routeTmp.lenStationList-1 ):
                            print('Counter', routeTmp.stationCounter)
                            routeTmp.train.addWagons(routeTmp.trainstations[routeTmp.stationCounter],routeTmp.trainstations[routeTmp.stationCounter+1] , routeTmp.wagons, routeTmp.player)
                            routeTmp.stationCounter += 1 
                            self.syncMoney()                                                      
                        else:
                            print('Counter', routeTmp.stationCounter)
                            routeTmp.train.addWagons(routeTmp.trainstations[-1],routeTmp.trainstations[0] , routeTmp.wagons, routeTmp.player)
                            routeTmp.stationCounter = 0                        
                            self.syncMoney()
                    else:
                        print("pass-Befehl ignoriert, da routeTmp == None (Route ist eine gelöschte Route)")
                        pass                
                else:
                    print("Client sendete fehlerhaften ROUTE-Befehl!")

            #Befehlsverarbeitung POS
            elif(args[0] == 'POS'):   
                #print("got pos update " + command)
                posX = int(args[1])
                posY = int(args[2])
                broadcast("POS+" + str(posX) + "+" + str(posY), exclude=self)
                
            else:
                print("Befehl nicht verstanden: ")
                print(command)

    #Server wartet im Thread auf Befehle des Clients bis dieser die Verbindung trennt
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
            

#-----------------STARTROUTINE-------------------#
            
#Wenn keine Config existiert wird eine neue mit diesen Einstellungen generiert:
DEFAULT_CONFIG = {
    'port': 2000,
    'bind_ip': 'localhost',
    'max_players': 5,
    'game' : {
        'prices': {
            'depot': 100,
            'station': 250,
            'terminal': 500,
            'bridge': 50,
            'rail': 20,
            'remove': 10,
        },
        'defaultmoney': 2000
    }
    }

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

gameloop = GameLoopThread(tickspeed=500)
gameloop.start()


print("Server wird gestartet...")
print(CONFIG)

#Warte stets auf eingehende Verbindungen von Clients
try:
    while True:
        connection, address = server.accept()
        print("Verbindungsaufbau von " + str(address) + "...")
        clientCount += 1
        thread = ClientThread(connection)
        thread.start()
        clients.append(thread)
        print("Anzahl verbundener Clients: " + str(clientCount))
        
#Wenn der Server beendet wird, werden Clients vorher vom Server getrennt        
except KeyboardInterrupt:
    for client in clients:
        client.disconnect()
    print("Server beendet")
