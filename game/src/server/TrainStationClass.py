from WayClass import WayLogic
from multiprocessing import Process
from threading import Thread
import time

class TrainStationLogic:
    
    PRODUCING = {
            'CORN': 100,
            'COLE': 100,
            'CITY': 50
            }
    NEEDED_RESSOURCES = {
            'CORN': 0,
            'COLE': 0,
            'CITY': 50
        }

    def __init__(self, pTile, pPlayer, pRange, pPrice,karte, tickspeed = 20):
        self. STORAGE = {
            'CORN': 0,
            'COLE': 0,
            'CITY': 0
        }         

        self.PRICES ={
            'CORN': 100,
            'COLE': 100,
            'CITY': 100
        }
        self.NUMBER_OF_PRODUCTION_BUILDINGS = {
            'CORN': 0,
            'COLE': 0,
            'CITY': 0
        }
        self.range = pRange
        self.price = pPrice
        self.x_Pos = pTile.getX()    
        self.y_Pos = pTile.getY()
        self.tile = pTile
        self.connectedRight = False; #rechtsverbunden?
        self.connectedLeft = False #linksverbunden?
        self.connectedUp = False #obenverbunden?
        self.connectedDown = False #untenverbunden?
        self.player = pPlayer # Spieler X  
        self.maxStorage = 2000  
        Thread.__init__(self)
        self.tickspeed = tickspeed/1000.0
        self.last_mach_was = 0
        self.running = False
        print('init')
        self.getProducingBuildings(karte)
        self.updatePrices()
        self.run()

    def updateStorage(self, pType):
        if(self.STORAGE[pType] <= self.maxStorage):                                 #Wenn noch Platz im Lager ist                 
                if(TrainStationLogic.NEEDED_RESSOURCES[pType] < self.STORAGE[pType]):   #überprüft ob genug Ressourcen vorhanden um zu Produzieren
                    self.STORAGE[pType] += TrainStationLogic.PRODUCING[pType]* self.NUMBER_OF_PRODUCTION_BUILDINGS[pType]        #fügt Produktion zum Lager hinzu  
                    self.STORAGE[pType] -= TrainStationLogic.NEEDED_RESSOURCES[pType]   #Ressourcen werden Verbraucht 
                    if(self.STORAGE[pType] >= self.maxStorage):
                        self.STORAGE[pType] = self.maxStorage            

    def do_loop(self):
        if(time.time() - self.last_mach_was > 1.2):
            print("1.2 sekunden sind um")
            for key in self.STORAGE:
	            self.updateStorage(key)
            self.last_mach_was = time.time()

    def run(self):
        print('test')
        self.running = True
        while self.running:
            self.do_loop()
            time.sleep(self.tickspeed)        


    def getProducingBuildings(self, karte):                    #fügt Produktionsgebäude hinzu      
        for i in range((-1*self.range), self.range+1):
            for j in range((-1*self.range), self.range+1):                
                if(self.x_Pos +i  >=0 and self.x_Pos + i <= 299 and self.y_Pos + j  >=0 and self.y_Pos +j <= 299):
                    if(karte[self.x_Pos+i][self.y_Pos+j].isProducingBuilding()):                    
                        self.NUMBER_OF_PRODUCTION_BUILDINGS[karte[self.x_Pos+i][self.y_Pos+j].getStringType()] += 1
        

    def updatePrices(self):
        for key in self.NUMBER_OF_PRODUCTION_BUILDINGS:
            self.PRICES[key] += 50 * self.NUMBER_OF_PRODUCTION_BUILDINGS[key]  

    def getType(self):        
        if(self.range == 2):            
            if(self.connectedRight == True or self.connectedLeft == True):                
                return 'DEPOT_H'
            if(self.connectedUp == True or self.connectedDown == True):                
                return 'DEPOT_V'

        if(self.range == 4):
            print('if range == 4 hat funktioniert')
            if(self.connectedRight == True or self.connectedLeft == True):
                return 'STATION_H'
            if(self.connectedUp == True or self.connectedDown == True):
                return 'STATION_V'

        if(self.range == 6):
            print('if range == 6 hat funktioniert')
            if(self.connectedRight == True or self.connectedLeft == True):
                return 'TERMINAL_H'
            if(self.connectedUp == True or self.connectedDown == True):
                return 'TERMINAL_V'


    @staticmethod
    def checkIfStationInRange(x_Pos, y_Pos, pPlayer, pRange, karte):
        sideLenght = 2*pRange+1             #Seitenlänge
        for column in range(pRange*2+1):    #Spalten    
            for row in range(pRange*2+1):   #Reihe
                if(karte[x_Pos][y_Pos].isTrainStation() and karte[x_Pos][y_Pos].logic.player == pPlayer):
                    return True
                else:
                    return False
    
    @staticmethod
    def checkConnectableRails(player, x_Pos, y_Pos, karte):
        railConnectableRight = False;   #Schiene rechts ist verbindbar?
        railConnectableLeft = False;    #Schiene links ist verbindbar?
        railConnectableUp = False;      #Schiene oben ist verbindbar?
        railConnectableDown = False;    #Schiene unten ist verbindbar?

        
        #Rechts
        if(x_Pos<299):                              #Wenn Rechts innerhalb der Karte liegt
            if(karte[x_Pos+1][y_Pos].isRail()): #Wenn Schiene existiert
                if(karte[x_Pos+1][y_Pos].logic.player == player): #Wenn Schiene zum selben Spieler gehoert
                    #Wenn Schiene nicht vollstaendig verbunden ist.
                    if(karte[x_Pos+1][y_Pos].logic.connectedRight + karte[x_Pos+1][y_Pos].logic.connectedLeft + karte[x_Pos+1][y_Pos].logic.connectedUp + karte[x_Pos+1][y_Pos].logic.connectedDown != 2):
                        railConnectableRight = True; #dann liegt rechts eine verbindbare Schiene
                        

        #Links
        if(x_Pos>0):                                #Wenn Links innerhalb der Karte liegt
            if(karte[x_Pos-1][y_Pos].isRail()): #Wenn Schiene existiert
                if(karte[x_Pos-1][y_Pos].logic.player == player): #Wenn Schiene zum selben Spieler gehoert
                    #Wenn Schiene nicht vollstaendig verbunden ist.
                    if(karte[x_Pos-1][y_Pos].logic.connectedRight + karte[x_Pos-1][y_Pos].logic.connectedLeft + karte[x_Pos-1][y_Pos].logic.connectedUp + karte[x_Pos-1][y_Pos].logic.connectedDown != 2):
                        railConnectableLeft = True;     #Dann liegt links eine verbindbare Schiene

        
        #Oben
        if(y_Pos>0):                                #Wenn Oben innerhalb der Karte liegt
            if(karte[x_Pos][y_Pos-1].isRail()): #Wenn Schiene existiert
                if(karte[x_Pos][y_Pos-1].logic.player == player): #Wenn Schiene zum selben Spieler gehoert 
                    #Wenn Schiene nicht vollstaendig verbunden ist.
                    if(karte[x_Pos][y_Pos-1].logic.connectedRight + karte[x_Pos][y_Pos-1].logic.connectedLeft + karte[x_Pos][y_Pos-1].logic.connectedUp + karte[x_Pos][y_Pos-1].logic.connectedDown != 2):
                        railConnectableUp = True;            #Dann liegt Oben eine verbindbare Schiene

        #Unten
        if(y_Pos<299):                              #Wenn Unten innerhalb der Karte liegt
            if(karte[x_Pos][y_Pos+1].isRail()): #Wenn Schiene existiert
                if(karte[x_Pos][y_Pos+1].logic.player == player): #Wenn Schiene zum selben Spieler gehoert
                    #Wenn Schiene nicht vollstaendig verbunden ist.
                    if(karte[x_Pos][y_Pos+1].logic.connectedRight + karte[x_Pos][y_Pos+1].logic.connectedLeft + karte[x_Pos][y_Pos+1].logic.connectedUp + karte[x_Pos][y_Pos+1].logic.connectedDown != 2):
                        railConnectableDown = True                  #Dann liegt Unten eine verbindbare Schiene
        
        return railConnectableRight, railConnectableLeft,  railConnectableUp, railConnectableDown

    @staticmethod
    def build(x_Pos, y_Pos, pPlayer, pRange, karte):        
        railConnectableRight, railConnectableLeft,  railConnectableUp, railConnectableDown = TrainStationLogic.checkConnectableRails(pPlayer,x_Pos ,y_Pos , karte)
        print(railConnectableRight, railConnectableLeft,  railConnectableUp, railConnectableDown)
        if(not TrainStationLogic.checkIfStationInRange(x_Pos, y_Pos, pPlayer, pRange, karte)):
            print("kein Bahnhof in Range")
            if(railConnectableUp + railConnectableDown + railConnectableRight + railConnectableLeft == 0): #Keine Schiene verbindbar.
                print("Bahnhöfe koennen nur an bestehendes Schienennetz gebaut werden!")

            if(railConnectableUp + railConnectableDown + railConnectableRight + railConnectableLeft == 1):   #Eine Schiene verbindbar.
                karte[x_Pos][y_Pos].initLogic(TrainStationLogic,  karte, pRange,)                
                if(railConnectableRight):                           #Verbindet mit rechter Schiene
                    karte[x_Pos][y_Pos].logic.connectedRight = True
                    karte[x_Pos+1][y_Pos].logic.connectedLeft = True
                    karte[x_Pos+1][y_Pos].logicUpdate()
                    if(karte[x_Pos+1][y_Pos].logic.way.firstTrainStation == None):                   #hinzufügen des Bahnhofs zur Strecke
                        karte[x_Pos+1][y_Pos].logic.way.firstTrainStation = karte[x_Pos][y_Pos]                                           
                    else:
                        karte[x_Pos+1][y_Pos].logic.way.secondTrainStation = karte[x_Pos][y_Pos]
                    if(karte[x_Pos+1][y_Pos].logic.way.firstRail[0].isTrainStation()):
                        karte[x_Pos+1][y_Pos].logic.way.firstRail.append(karte[x_Pos][y_Pos])
                        karte[x_Pos+1][y_Pos].logic.way.secondRail.append(None)
                    else:
                        karte[x_Pos+1][y_Pos].logic.way.firstRail.insert(0, karte[x_Pos][y_Pos])
                        karte[x_Pos+1][y_Pos].logic.way.secondRail.insert(0, None)                       
                if(railConnectableLeft):                            #Verbindet mit linker Schiene                    
                    karte[x_Pos][y_Pos].logic.connectedLeft = True
                    karte[x_Pos-1][y_Pos].logic.connectedRight = True
                    karte[x_Pos-1][y_Pos].logicUpdate()
                    if(karte[x_Pos-1][y_Pos].logic.way.firstTrainStation == None):                   #hinzufügen des Bahnhofs zur Strecke
                        karte[x_Pos-1][y_Pos].logic.way.firstTrainStation = karte[x_Pos][y_Pos]
                    else:
                        karte[x_Pos-1][y_Pos].logic.way.secondTrainStation = karte[x_Pos][y_Pos]
                    if(karte[x_Pos-1][y_Pos].logic.way.firstRail[0].isTrainStation()):
                        karte[x_Pos-1][y_Pos].logic.way.firstRail.append(karte[x_Pos][y_Pos])
                        karte[x_Pos-1][y_Pos].logic.way.secondRail.append(None)
                    else:
                        karte[x_Pos-1][y_Pos].logic.way.firstRail.insert(0, karte[x_Pos][y_Pos])
                        karte[x_Pos-1][y_Pos].logic.way.secondRail.insert(0, None)
                if(railConnectableUp):                              #Verbindet mit oberer Schiene
                    karte[x_Pos][y_Pos].logic.connectedUp = True
                    karte[x_Pos][y_Pos-1].logic.connectedDown = True
                    karte[x_Pos][y_Pos-1].logicUpdate()
                    if(karte[x_Pos][y_Pos-1].logic.way.firstTrainStation == None):                   #hinzufügen des Bahnhofs zur Strecke
                        karte[x_Pos][y_Pos-1].logic.way.firstTrainStation = karte[x_Pos][y_Pos]
                    else:
                        karte[x_Pos][y_Pos-1].logic.way.secondTrainStation = karte[x_Pos][y_Pos]
                    if(karte[x_Pos][y_Pos-1].logic.way.firstRail[0].isTrainStation()):
                        karte[x_Pos][y_Pos-1].logic.way.firstRail.append(karte[x_Pos][y_Pos])
                        karte[x_Pos][y_Pos-1].logic.way.secondRail.append(None)
                    else:
                        karte[x_Pos][y_Pos-1].logic.way.firstRail.insert(0, karte[x_Pos][y_Pos])
                        karte[x_Pos][y_Pos-1].logic.way.secondRail.insert(0, None)
                if(railConnectableDown):                           #Verbindet mit unterer Schiene
                    karte[x_Pos][y_Pos].logic.connectedDown = True
                    karte[x_Pos][y_Pos+1].logic.connectedUp = True
                    karte[x_Pos][y_Pos+1].logicUpdate()
                    if(karte[x_Pos][y_Pos+1].logic.way.firstTrainStation == None):                   #hinzufügen des Bahnhofs zur Strecke
                        karte[x_Pos][y_Pos+1].logic.way.firstTrainStation = karte[x_Pos][y_Pos]
                    else:
                        karte[x_Pos][y_Pos+1].logic.way.secondTrainStation = karte[x_Pos][y_Pos]
                    if(karte[x_Pos][y_Pos+1].logic.way.firstRail[0].isTrainStation()):
                        karte[x_Pos][y_Pos+1].logic.way.firstRail.append(karte[x_Pos][y_Pos])
                        karte[x_Pos][y_Pos+1].logic.way.secondRail.append(None)
                    else:
                        karte[x_Pos][y_Pos+1].logic.way.firstRail.insert(0, karte[x_Pos][y_Pos])
                        karte[x_Pos][y_Pos+1].logic.way.secondRail.insert(0, None)
                karte[x_Pos][y_Pos].logicUpdate()                       #Logik Update Bahnhof

            if(railConnectableUp + railConnectableDown + railConnectableRight + railConnectableLeft == 2):   #Zwei Schiene verbindbar.
                karte[x_Pos][y_Pos].initLogic(TrainStationLogic,  karte, pRange,)
                if(railConnectableRight and railConnectableLeft): #Verbindet mit rechter Schiene und linker Schiene
                    karte[x_Pos][y_Pos].logic.connectedRight = True
                    karte[x_Pos+1][y_Pos].logic.connectedLeft = True
                    karte[x_Pos][y_Pos].logic.connectedLeft = True
                    karte[x_Pos-1][y_Pos].connectedRight = True
                    karte[x_Pos+1][y_Pos].logicUpdate()             #Logik Update Rechts
                    karte[x_Pos-1][y_Pos].logicUpdate()             #Logik Update Links
                    if(karte[x_Pos+1][y_Pos].logic.way.firstTrainStation == None):                   #hinzufügen des Bahnhofs zur Strecke
                        karte[x_Pos+1][y_Pos].logic.way.firstTrainStation = karte[x_Pos][y_Pos]                        
                        karte[x_Pos+1][y_Pos].logic.way.firstRail.append(karte[x_Pos][y_Pos])
                        karte[x_Pos+1][y_Pos].logic.way.secondRail.append(None)
                    else:
                        karte[x_Pos+1][y_Pos].logic.way.secondTrainStation = karte[x_Pos][y_Pos]
                        karte[x_Pos+1][y_Pos].logic.way.firstRail.append(karte[x_Pos][y_Pos])
                        karte[x_Pos+1][y_Pos].logic.way.secondRail.append(None)
                    if(karte[x_Pos-1][y_Pos].logic.way.firstTrainStation == None):                   #hinzufügen des Bahnhofs zur Strecke
                        karte[x_Pos-1][y_Pos].logic.way.firstTrainStation = karte[x_Pos][y_Pos]
                        karte[x_Pos-1][y_Pos].logic.way.firstRail.append(karte[x_Pos][y_Pos])
                        karte[x_Pos-1][y_Pos].logic.way.secondRail.append(None)
                    else:
                        karte[x_Pos-1][y_Pos].logic.way.secondTrainStation = karte[x_Pos][y_Pos]
                        karte[x_Pos-1][y_Pos].logic.way.firstRail.append(karte[x_Pos][y_Pos])
                        karte[x_Pos-1][y_Pos].logic.way.secondRail.append(None)

                if(railConnectableUp and railConnectableDown): #Verbindet mit oberer Schiene und unterer Schiene
                    karte[x_Pos][y_Pos].logic.connectedUp = True
                    karte[x_Pos][y_Pos-1].logic.connectedDown = True
                    karte[x_Pos][y_Pos].logic.connectedDown = True
                    karte[x_Pos][y_Pos+1].logic.connectedUp = True
                    karte[x_Pos][y_Pos-1].logicUpdate()            #Logik Update Oben
                    karte[x_Pos][y_Pos+1].logicUpdate()            #Logik Update Unten
                    if(karte[x_Pos][y_Pos-1].logic.way.firstTrainStation == None):                   #hinzufügen des Bahnhofs zur Strecke
                        karte[x_Pos][y_Pos-1].logic.way.firstTrainStation = karte[x_Pos][y_Pos]
                        karte[x_Pos][y_Pos-1].logic.way.firstRail.append(karte[x_Pos][y_Pos])
                        karte[x_Pos][y_Pos-1].logic.way.firstRail.append(None)
                    else:
                        karte[x_Pos][y_Pos-1].logic.way.secondTrainStation = karte[x_Pos][y_Pos]
                        karte[x_Pos][y_Pos-1].logic.way.firstRail.append(karte[x_Pos][y_Pos])
                        karte[x_Pos][y_Pos-1].logic.way.firstRail.append(None)
                    if(karte[x_Pos][y_Pos+1].logic.way.firstTrainStation == None):                   #hinzufügen des Bahnhofs zur Strecke
                        karte[x_Pos][y_Pos+1].logic.way.firstTrainStation = karte[x_Pos][y_Pos]
                        karte[x_Pos][y_Pos+1].logic.way.firstRail.append(karte[x_Pos][y_Pos])
                        karte[x_Pos][y_Pos+1].logic.way.secondRail.append(None)
                    else:
                        karte[x_Pos][y_Pos+1].logic.way.secondTrainStation = karte[x_Pos][y_Pos]
                        karte[x_Pos][y_Pos+1].logic.way.firstRail.append(karte[x_Pos][y_Pos])
                        karte[x_Pos][y_Pos+1].logic.way.secondRail.append(None)
                karte[x_Pos][y_Pos].logicUpdate()                   #Logik Update Bahnhof
            
        else:
            print('Kann Bahnhof hier nicht bauen!')

    def remove(self, x_Pos,y_Pos, pPlayer, karte): 
        if(karte[x_Pos][y_Pos].player == pPlayer):
            if(self.connectedRight + self.connectedLeft + self.connectedUp +self.connectedDown == 1):
                karte[x_Pos][y_Pos].setType('GRASS')    #Maptile wird wieder auf Gras gesetzt
                if(self.connectedRight == True):        
                    karte[x_Pos+1][y_Pos].logic.connectedLeft = False  #entfernt Verbindungen von anderen Schienen
                    if(karte[x_Pos+1][y_Pos].logic.way.firstStation == karte[x_Pos][y_Pos]): 
                        karte[x_Pos+1][y_Pos].logic.way.firstStation = None #entfernt ersten Bahnhof
                    else:
                        karte[x_Pos+1][y_Pos].logic.way.secondStation = None #entfernt zweiten Bahnhof
                tmp = karte[x_Pos+1][y_Pos].logic.way.firstRail.index(karte[x_Pos][y_Pos])    #entfernt Gleis aus Strecke
                del karte[x_Pos+1][y_Pos].logic.way.firstRail[tmp]            
                del karte[x_Pos+1][y_Pos].logic.way.secondRail[tmp] 
                if(self.connectedLeft == True):
                    karte[x_Pos-1][y_Pos].logic.connectedRight = False #entfernt Verbindungen von anderen Schienen
                    if(karte[x_Pos-1][y_Pos].logic.way.firstStation == karte[x_Pos][y_Pos]):
                        karte[x_Pos-1][y_Pos].logic.way.firstStation = None #entfernt ersten Bahnhof
                    else:
                        karte[x_Pos-1][y_Pos].logic.way.secondStation = None #entfernt zweiten Bahnhof
                    tmp = karte[x_Pos-1][y_Pos].logic.way.firstRail.index(karte[x_Pos][y_Pos])    #entfernt Gleis aus Strecke
                    del karte[x_Pos-1][y_Pos].logic.way.firstRail[tmp]            
                    del karte[x_Pos-1][y_Pos].logic.way.secondRail[tmp] 
                if(self.connectedUp == True):
                    karte[x_Pos][y_Pos-1].logic.connectedDown = False  #entfernt Verbindungen von anderen Schienen
                    if(karte[x_Pos][y_Pos-1].logic.way.firstStation == karte[x_Pos][y_Pos]):
                        karte[x_Pos][y_Pos-1].logic.way.firstStation = None #entfernt ersten Bahnhof
                    else:
                        karte[x_Pos][y_Pos-1].logic.way.secondStation = None #entfernt zweiten Bahnhof
                    tmp = karte[x_Pos][y_Pos-1].logic.way.firstRail.index(karte[x_Pos][y_Pos])    #entfernt Gleis aus Strecke
                    del karte[x_Pos][y_Pos-1].logic.way.firstRail[tmp]            
                    del karte[x_Pos][y_Pos-1].logic.way.secondRail[tmp] 
                if(self.connectedDown == True):
                    karte[x_Pos][y_Pos+1].logic.connectedUp = False    #entfernt Verbindungen von anderen Schienen
                    if(karte[x_Pos][y_Pos+1].logic.way.firstStation == karte[x_Pos][y_Pos]):
                        karte[x_Pos][y_Pos].logic.way.firstStation = None     #entfernt ersten Bahnhof              
                    else:
                        karte[x_Pos][y_Pos-1].logic.way.secondStation = None #entfernt zweiten Bahnhof
                    tmp = karte[x_Pos][y_Pos].logic.way.firstRail.index(karte[x_Pos][y_Pos])    #entfernt Gleis aus Strecke
                    del karte[x_Pos][y_Pos+1].logic.way.firstRail[tmp]            
                    del karte[x_Pos][y_Pos+1].logic.way.secondRail[tmp] 
                                                                    
                karte[x_Pos][y_Pos].logic = None        #setzt Logic Objekt auf None
