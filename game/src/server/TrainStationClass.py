from WayClass import WayLogic
from multiprocessing import Process
from threading import Thread
import time

#Die Objekte dieser Klasse speichern Ressourcen und dienen der Route als Haltepunkte. Jeder Bahnhof hat je nach Typ einen anderen Radius in dem er Ressourcen sammeln kann.
class TrainStationLogic:

    #Ressourcen-Daten des Bahnhofs:
    PRODUCING = {
            'CORN': 20,
            'COAL': 20,
            'PASSENGERS': 10,
            'MAIL' : 10,
            'LIVESTOCK': 10,
            'GOODS': 10,
            'PAPER': 10,
            'STEEL': 10,
            'PETROLEUM': 10,
            'WOOD': 20,
            'FOOD': 10,
            'NOTHING': 0
            }
    NEEDED_RESSOURCES = {
            'CORN': {
                'NOTHING': 0
            },

            'COAL': {
                'NOTHING': 0
            },
            'PASSENGERS':{
                'PASSENGERS': 50,
                'MAIL': 50,
                'FOOD': 100,
                'GOODS': 200,
                'PAPER': 100,
                'PETROLEUM': 50,
                'CORN': 20
            },
            'MAIL' : {
                'NOTHING': 0
            },
            'LIVESTOCK': {
                'CORN': 50
            },
            'GOODS': {
                'WOOD': 50,
                'STEEL': 50
            },
            'PAPER': {
                'WOOD': 50
            },
            'STEEL': {
                'COAL': 50
            },
            'PETROLEUM': {
                'NOTHING': 0
            },
            'WOOD': {
                'NOTHING': 0
            },
            'FOOD': {
                'LIVESTOCK': 50
            }, 
            'NOTHING':{
                'NOTHING': 0 #Nur für die Logik
            }       }


    def __init__(self, pTile, pPlayer, pRange, pPrice,karte, tickspeed = 20):
        self. STORAGE = {
            'CORN': 0,
            'COAL': 0,
            'PASSENGERS': 0,
            'MAIL': 0,
            'LIVESTOCK': 0,
            'GOODS': 0,
            'PAPER': 0,
            'STEEL': 0,
            'PETROLEUM': 0,
            'WOOD': 0,
            'FOOD': 0,
            'NOTHING' : 0 #Wert nur für Logik der Funktionen 
        }         

        self.PRICES ={
            'CORN': 20,
            'COAL': 20,
            'PASSENGERS': 20,
            'MAIL': 20,
            'LIVESTOCK': 30,
            'GOODS': 20,
            'PAPER': 30,
            'STEEL': 30,
            'PETROLEUM': 30,
            'WOOD': 20,
            'FOOD': 35,
            'NOTHING': 0

        }
        self.NUMBER_OF_PRODUCTION_BUILDINGS = {
            'CORN': 0,
            'COAL': 0,
            'PASSENGERS': 0,
            'MAIL': 0,
            'LIVESTOCK': 0,
            'GOODS': 0,
            'PAPER': 0,
            'STEEL': 0,
            'PETROLEUM': 0,
            'WOOD': 0,
            'FOOD': 0,
            'NOTHING': 0,

            
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
        #self.run()

    def updateStorage(self, pType):
        if(self.STORAGE[pType] <= self.maxStorage):                                 #Wenn noch Platz im Lager ist                 
            boolTmp = 0
            #print(pType)
            if(pType != 'PASSENGERS' and self.NUMBER_OF_PRODUCTION_BUILDINGS[pType] > 0):
                #print('Anzahl Produktionsgebäude:',pType , self.NUMBER_OF_PRODUCTION_BUILDINGS)
                for keys in TrainStationLogic.NEEDED_RESSOURCES[pType]:  #überprüft ob genug Ressourcen vorhanden um zu Produzieren
                    if(self.STORAGE[keys] <  TrainStationLogic.NEEDED_RESSOURCES[pType][keys]):
                        boolTmp += 1
                #print('boolTmp:' ,boolTmp)               
                if(boolTmp == 0 ):   #überprüft ob genug Ressourcen vorhanden um zu Produzieren
                    if(pType != 'PASSENGERS'):                        
                        self.STORAGE[pType] += TrainStationLogic.PRODUCING[pType]* self.NUMBER_OF_PRODUCTION_BUILDINGS[pType]        #fügt Produktion zum Lager hinzu  
                    for keys in TrainStationLogic.NEEDED_RESSOURCES[pType] : 
                        if(pType != 'PASSENGERS'):                  
                            self.STORAGE[pType] -= TrainStationLogic.NEEDED_RESSOURCES[pType][keys]*self.NUMBER_OF_PRODUCTION_BUILDINGS[pType]   #Ressourcen werden Verbraucht 
                    #print(pType,":", self.STORAGE[pType])
                    if(self.STORAGE[pType] >= self.maxStorage):
                        if(pType != 'PASSENGERS'):
                            self.STORAGE[pType] = self.maxStorage
            else:
                self.STORAGE[pType] += TrainStationLogic.PRODUCING[pType]* self.NUMBER_OF_PRODUCTION_BUILDINGS[pType]    
                #print(pType,":", self.STORAGE[pType])
                #print('Anzahl Produktionsgebäude', self.NUMBER_OF_PRODUCTION_BUILDINGS[pType])
            return True            
        return False    
    def do_loop(self):
        if(time.time() - self.last_mach_was > 1.2):
            #print("1.2 sekunden sind um")
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
                    #print(karte[self.x_Pos+i][self.y_Pos+j].getStringType())
                    if(karte[self.x_Pos+i][self.y_Pos+j].isProducingBuilding()):                        
                        if(karte[self.x_Pos+i][self.y_Pos+j].getType() == 2):
                            self.NUMBER_OF_PRODUCTION_BUILDINGS['PASSENGERS'] += 1
                            self.NUMBER_OF_PRODUCTION_BUILDINGS['MAIL'] += 1                        
                        else:
                            self.NUMBER_OF_PRODUCTION_BUILDINGS[karte[self.x_Pos+i][self.y_Pos+j].getStringType()] += 1
        

    def updatePrices(self):
        self.PRICES['CORN'] += int(round(TrainStationLogic.NEEDED_RESSOURCES['LIVESTOCK']['CORN']*self.NUMBER_OF_PRODUCTION_BUILDINGS['LIVESTOCK']/30))
        self.PRICES['CORN'] += int(round(TrainStationLogic.NEEDED_RESSOURCES['PASSENGERS']['CORN']*self.NUMBER_OF_PRODUCTION_BUILDINGS['PASSENGERS']/30))
        self.PRICES['COAL'] += int(round(TrainStationLogic.NEEDED_RESSOURCES['STEEL']['COAL']*self.NUMBER_OF_PRODUCTION_BUILDINGS['STEEL']/30))
        self.PRICES['PASSENGERS'] += int(round(TrainStationLogic.NEEDED_RESSOURCES['PASSENGERS']['PASSENGERS']*self.NUMBER_OF_PRODUCTION_BUILDINGS['PASSENGERS']/30))
        self.PRICES['MAIL'] += int(round(TrainStationLogic.NEEDED_RESSOURCES['PASSENGERS']['MAIL']*self.NUMBER_OF_PRODUCTION_BUILDINGS['PASSENGERS']/30))
        self.PRICES['LIVESTOCK'] += int(round(TrainStationLogic.NEEDED_RESSOURCES['FOOD']['LIVESTOCK']*self.NUMBER_OF_PRODUCTION_BUILDINGS['FOOD']/30))
        self.PRICES['GOODS'] += int(round(TrainStationLogic.NEEDED_RESSOURCES['PASSENGERS']['GOODS']*self.NUMBER_OF_PRODUCTION_BUILDINGS['PASSENGERS']/30))
        self.PRICES['PAPER'] += int(round(TrainStationLogic.NEEDED_RESSOURCES['PASSENGERS']['PAPER']*self.NUMBER_OF_PRODUCTION_BUILDINGS['PASSENGERS']/30))
        self.PRICES['STEEL'] += int(round(TrainStationLogic.NEEDED_RESSOURCES['GOODS']['STEEL']*self.NUMBER_OF_PRODUCTION_BUILDINGS['GOODS']/30))
        self.PRICES['PETROLEUM'] += int(round(TrainStationLogic.NEEDED_RESSOURCES['PASSENGERS']['PETROLEUM']*self.NUMBER_OF_PRODUCTION_BUILDINGS['PASSENGERS']/30))
        self.PRICES['WOOD'] += int(round(TrainStationLogic.NEEDED_RESSOURCES['PAPER']['WOOD']*self.NUMBER_OF_PRODUCTION_BUILDINGS['PAPER']/30))
        self.PRICES['WOOD'] += int(round(TrainStationLogic.NEEDED_RESSOURCES['GOODS']['WOOD']*self.NUMBER_OF_PRODUCTION_BUILDINGS['GOODS']/30))
        self.PRICES['FOOD'] += int(round(TrainStationLogic.NEEDED_RESSOURCES['PASSENGERS']['FOOD']*self.NUMBER_OF_PRODUCTION_BUILDINGS['PASSENGERS']/30))

    def getType(self):  #gibt Typ des Bahnhofs zurück        
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

    def getProtocolStringPrices(self):  #gibt Protokollstring für Preise zurück
        print('start')
        s='INFO+PRICE+'
        for keys in self.PRICES.keys():
            if(keys != 'NOTHING'):
                s+= str(self.PRICES[keys])+' \n'
        print(s)
        
        return s[:-2]

    def getProtocolStringStorage(self): #gibt Protokollstring für Lager zurück
        s='INFO+STORE+'
        for keys in self.STORAGE.keys():
            if(keys != 'NOTHING'):
                s+= str(self.STORAGE[keys])+' \n'
        print(s)
        return s[:-2]


    
    #Prüft ob eine Kachel in Reichweite zur Trainstation ist
    @staticmethod
    def checkIfStationInRange(x_Pos, y_Pos, pPlayer, pRange, karte):    
        sideLenght = 2*pRange+1             #Seitenlänge
        for column in range(pRange*2+1):    #Spalten    
            for row in range(pRange*2+1):   #Reihe
                if(karte[x_Pos][y_Pos].isTrainStation() and karte[x_Pos][y_Pos].logic.player == pPlayer):
                    return True
                else:
                    return False

    #Schienen dürfen nur gelegt werden, wenn andere Schiene oder Bahnhof in der Nähe ist
    @staticmethod
    def checkConnectableRails(player, x_Pos, y_Pos, karte):     
        railConnectableRight = False;   #Schiene rechts ist verbindbar?
        railConnectableLeft = False;    #Schiene links ist verbindbar?
        railConnectableUp = False;      #Schiene oben ist verbindbar?
        railConnectableDown = False;    #Schiene unten ist verbindbar?
        print("start: ", x_Pos)
        
        #Rechts
        if(x_Pos<299):                              #Wenn Rechts innerhalb der Karte liegt
            print(karte[x_Pos+1][y_Pos].getType())
            print(karte[x_Pos+1][y_Pos].isRail())
            if(karte[x_Pos+1][y_Pos].isRail()): #Wenn Schiene existiert
                'Schiene existiert'
                if(karte[x_Pos+1][y_Pos].logic.player == player): #Wenn Schiene zum selben Spieler gehoert
                    #Wenn Schiene nicht vollstaendig verbunden ist.
                    print("gleicher Spieler")
                    'Schiene nicht vollstänig verbundn'
                    print(karte[x_Pos+1][y_Pos].logic.connectedRight + karte[x_Pos+1][y_Pos].logic.connectedLeft + karte[x_Pos+1][y_Pos].logic.connectedUp + karte[x_Pos+1][y_Pos].logic.connectedDown)
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

    #Diese Funktion ermöglicht den Bau von Schienen + Kurvenlogik
    @staticmethod
    def build(x_Pos, y_Pos, pPlayer, pRange, karte):        
        railConnectableRight, railConnectableLeft,  railConnectableUp, railConnectableDown = TrainStationLogic.checkConnectableRails(pPlayer,x_Pos ,y_Pos , karte)
        print(railConnectableRight, railConnectableLeft,  railConnectableUp, railConnectableDown)
        if(not TrainStationLogic.checkIfStationInRange(x_Pos, y_Pos, pPlayer, pRange, karte)):
            print("kein Bahnhof in Range")
            if(railConnectableUp + railConnectableDown + railConnectableRight + railConnectableLeft == 0): #Keine Schiene verbindbar.
                print("Bahnhöfe koennen nur an bestehendes Schienennetz gebaut werden!")
                return False

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
            return False

        return True

    #Entferne Das Maptile und setze es auf Gras zurück
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
