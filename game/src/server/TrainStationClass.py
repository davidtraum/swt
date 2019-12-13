from WayClass import WayLogic
class TrainStationLogic:
    def __init__(self, pTile, pPlayer, pRange, pPrice):
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


    def getType(self):
        print(self.range)
        if(self.range == 2):
            print('if range == 2 hat funktioniert')
            if(self.connectedRight == True or self.connectedLeft == True):
                print('if Horizontal hat funktioniert')
                return 'DEPOT_H'
            if(self.connectedUp == True or self.connectedDown == True):
                print('if Vertikal hat funktioniert')
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
    def checkIfStationInRange(x_pos, y_pos, pPlayer, pRange, karte):
        sideLenght = 2*pRange+1             #Seitenlänge
        for column in range(pRange*2+1):    #Spalten    
            for row in range(pRange*2+1):   #Reihe
                if(karte[x_pos][y_pos].isTrainStation() and karte[x_pos][y_pos].logic.player == pPlayer):
                    return True
                else:
                    return False
    
    @staticmethod
    def checkConnectableRails(player, x_pos, y_pos, karte):
        railConnectableRight = False;   #Schiene rechts ist verbindbar?
        railConnectableLeft = False;    #Schiene links ist verbindbar?
        railConnectableUp = False;      #Schiene oben ist verbindbar?
        railConnectableDown = False;    #Schiene unten ist verbindbar?

        print("Start checkConnectalbeRails")
        #Rechts
        if(x_pos<299):                              #Wenn Rechts innerhalb der Karte liegt
            if(karte[x_pos+1][y_pos].isRail()): #Wenn Schiene existiert
                if(karte[x_pos+1][y_pos].logic.player == player): #Wenn Schiene zum selben Spieler gehoert
                    #Wenn Schiene nicht vollstaendig verbunden ist.
                    if(karte[x_pos+1][y_pos].logic.connectedRight + karte[x_pos+1][y_pos].logic.connectedLeft + karte[x_pos+1][y_pos].logic.connectedUp + karte[x_pos+1][y_pos].logic.connectedDown != 2):
                        railConnectableRight = True; #dann liegt rechts eine verbindbare Schiene
                        

        #Links
        if(x_pos>0):                                #Wenn Links innerhalb der Karte liegt
            if(karte[x_pos-1][y_pos].isRail()): #Wenn Schiene existiert
                if(karte[x_pos-1][y_pos].logic.player == player): #Wenn Schiene zum selben Spieler gehoert
                    #Wenn Schiene nicht vollstaendig verbunden ist.
                    if(karte[x_pos-1][y_pos].logic.connectedRight + karte[x_pos-1][y_pos].logic.connectedLeft + karte[x_pos-1][y_pos].logic.connectedUp + karte[x_pos-1][y_pos].logic.connectedDown != 2):
                        railConnectableLeft = True;     #Dann liegt links eine verbindbare Schiene

        
        #Oben
        if(y_pos>0):                                #Wenn Oben innerhalb der Karte liegt
            if(karte[x_pos][y_pos-1].isRail()): #Wenn Schiene existiert
                if(karte[x_pos][y_pos-1].logic.player == player): #Wenn Schiene zum selben Spieler gehoert 
                    #Wenn Schiene nicht vollstaendig verbunden ist.
                    if(karte[x_pos][y_pos-1].logic.connectedRight + karte[x_pos][y_pos-1].logic.connectedLeft + karte[x_pos][y_pos-1].logic.connectedUp + karte[x_pos][y_pos-1].logic.connectedDown != 2):
                        railConnectableUp = True;            #Dann liegt Oben eine verbindbare Schiene

        #Unten
        if(y_pos<299):                              #Wenn Unten innerhalb der Karte liegt
            if(karte[x_pos][y_pos+1].isRail()): #Wenn Schiene existiert
                if(karte[x_pos][y_pos+1].logic.player == player): #Wenn Schiene zum selben Spieler gehoert
                    #Wenn Schiene nicht vollstaendig verbunden ist.
                    if(karte[x_pos][y_pos+1].logic.connectedRight + karte[x_pos][y_pos+1].logic.connectedLeft + karte[x_pos][y_pos+1].logic.connectedUp + karte[x_pos][y_pos+1].logic.connectedDown != 2):
                        railConnectableDown = True                  #Dann liegt Unten eine verbindbare Schiene
        print('Werte von Checkrails')
        return railConnectableRight, railConnectableLeft,  railConnectableUp, railConnectableDown

    @staticmethod
    def build(x_pos, y_pos, pPlayer, pRange, karte):        
        railConnectableRight, railConnectableLeft,  railConnectableUp, railConnectableDown = TrainStationLogic.checkConnectableRails(pPlayer,x_pos ,y_pos , karte)
        print(railConnectableRight, railConnectableLeft,  railConnectableUp, railConnectableDown)
        if(not TrainStationLogic.checkIfStationInRange(x_pos, y_pos, pPlayer, pRange, karte)):
            print("kein Bahnhof in Range")
            if(railConnectableUp + railConnectableDown + railConnectableRight + railConnectableLeft == 0): #Keine Schiene verbindbar.
                print("Bahnhöfe koennen nur an bestehendes Schienennetz gebaut werden!")

            if(railConnectableUp + railConnectableDown + railConnectableRight + railConnectableLeft == 1):   #Eine Schiene verbindbar.
                karte[x_pos][y_pos].initLogic(TrainStationLogic, pRange)
                if(railConnectableRight):                           #Verbindet mit rechter Schiene
                    karte[x_pos][y_pos].logic.connectedRight = True
                    karte[x_pos+1][y_pos].logic.connectedLeft = True
                    karte[x_pos+1][y_pos].logicUpdate()
                    if(karte[x_pos+1][y_pos].logic.way.firstTrainStation == None):                   #hinzufügen des Bahnhofs zur Strecke
                        karte[x_pos+1][y_pos].logic.way.firstTrainStation = karte[x_pos][y_pos]                        
                        karte[x_pos+1][y_pos].logic.way.firstRail.append(karte[x_pos][y_pos])
                        karte[x_pos+1][y_pos].logic.way.secondRail.append(None)
                    else:
                        karte[x_pos+1][y_pos].logic.way.secondTrainStation = karte[x_pos][y_pos]
                        karte[x_pos+1][y_pos].logic.way.firstRail.append(karte[x_pos][y_pos])
                        karte[x_pos+1][y_pos].logic.way.secondRail.append(None)
                if(railConnectableLeft):                            #Verbindet mit linker Schiene                    
                    karte[x_pos][y_pos].logic.connectedLeft = True
                    karte[x_pos-1][y_pos].logic.connectedRight = True
                    karte[x_pos-1][y_pos].logicUpdate()
                    if(karte[x_pos-1][y_pos].logic.way.firstTrainStation == None):                   #hinzufügen des Bahnhofs zur Strecke
                        karte[x_pos-1][y_pos].logic.way.firstTrainStation = karte[x_pos][y_pos]
                        karte[x_pos-1][y_pos].logic.way.firstRail.append(karte[x_pos][y_pos])
                        karte[x_pos-1][y_pos].logic.way.secondRail.append(None)
                    else:
                        karte[x_pos-1][y_pos].logic.way.secondTrainStation = karte[x_pos][y_pos]
                        karte[x_pos-1][y_pos].logic.way.firstRail.append(karte[x_pos][y_pos])
                        karte[x_pos-1][y_pos].logic.way.secondRail.append(None)
                if(railConnectableUp):                              #Verbindet mit oberer Schiene
                    karte[x_pos][y_pos].logic.connectedUp = True
                    karte[x_pos][y_pos-1].logic.connectedDown = True
                    karte[x_pos][y_pos-1].logicUpdate()
                    if(karte[x_pos][y_pos-1].logic.way.firstTrainStation == None):                   #hinzufügen des Bahnhofs zur Strecke
                        karte[x_pos][y_pos-1].logic.way.firstTrainStation = karte[x_pos][y_pos]
                        karte[x_pos][y_pos-1].logic.way.firstRail.append(karte[x_pos][y_pos])
                        karte[x_pos][y_pos-1].logic.way.firstRail.append(None)
                    else:
                        karte[x_pos][y_pos-1].logic.way.secondTrainStation = karte[x_pos][y_pos]
                        karte[x_pos][y_pos-1].logic.way.firstRail.append(karte[x_pos][y_pos])
                        karte[x_pos][y_pos-1].logic.way.firstRail.append(None)
                if(railConnectableDown):                           #Verbindet mit unterer Schiene
                    karte[x_pos][y_pos].logic.connectedDown = True
                    karte[x_pos][y_pos+1].logic.connectedUp = True
                    karte[x_pos][y_pos+1].logicUpdate()
                    if(karte[x_pos][y_pos+1].logic.way.firstTrainStation == None):                   #hinzufügen des Bahnhofs zur Strecke
                        karte[x_pos][y_pos+1].logic.way.firstTrainStation = karte[x_pos][y_pos]
                        karte[x_pos][y_pos+1].logic.way.firstRail.append(karte[x_pos][y_pos])
                        karte[x_pos][y_pos+1].logic.way.secondRail.append(None)
                    else:
                        karte[x_pos][y_pos+1].logic.way.secondTrainStation = karte[x_pos][y_pos]
                        karte[x_pos][y_pos+1].logic.way.firstRail.append(karte[x_pos][y_pos])
                        karte[x_pos][y_pos+1].logic.way.secondRail.append(None)
                karte[x_pos][y_pos].logicUpdate()                       #Logik Update Bahnhof

            if(railConnectableUp + railConnectableDown + railConnectableRight + railConnectableLeft == 2):   #Zwei Schiene verbindbar.
                karte[x_pos][y_pos].initLogic(TrainStationLogic, pRange)
                if(railConnectableRight and railConnectableLeft): #Verbindet mit rechter Schiene und linker Schiene
                    karte[x_pos][y_pos].logic.connectedRight = True
                    karte[x_pos+1][y_pos].logic.connectedLeft = True
                    karte[x_pos][y_pos].logic.connectedLeft = True
                    karte[x_pos-1][y_pos].connectedRight = True
                    karte[x_pos+1][y_pos].logicUpdate()             #Logik Update Rechts
                    karte[x_pos-1][y_pos].logicUpdate()             #Logik Update Links
                    if(karte[x_pos+1][y_pos].logic.way.firstTrainStation == None):                   #hinzufügen des Bahnhofs zur Strecke
                        karte[x_pos+1][y_pos].logic.way.firstTrainStation = karte[x_pos][y_pos]                        
                        karte[x_pos+1][y_pos].logic.way.firstRail.append(karte[x_pos][y_pos])
                        karte[x_pos+1][y_pos].logic.way.secondRail.append(None)
                    else:
                        karte[x_pos+1][y_pos].logic.way.secondTrainStation = karte[x_pos][y_pos]
                        karte[x_pos+1][y_pos].logic.way.firstRail.append(karte[x_pos][y_pos])
                        karte[x_pos+1][y_pos].logic.way.secondRail.append(None)
                    if(karte[x_pos-1][y_pos].logic.way.firstTrainStation == None):                   #hinzufügen des Bahnhofs zur Strecke
                        karte[x_pos-1][y_pos].logic.way.firstTrainStation = karte[x_pos][y_pos]
                        karte[x_pos-1][y_pos].logic.way.firstRail.append(karte[x_pos][y_pos])
                        karte[x_pos-1][y_pos].logic.way.secondRail.append(None)
                    else:
                        karte[x_pos-1][y_pos].logic.way.secondTrainStation = karte[x_pos][y_pos]
                        karte[x_pos-1][y_pos].logic.way.firstRail.append(karte[x_pos][y_pos])
                        karte[x_pos-1][y_pos].logic.way.secondRail.append(None)

                if(railConnectableUp and railConnectableDown): #Verbindet mit oberer Schiene und unterer Schiene
                    karte[x_pos][y_pos].logic.connectedUp = True
                    karte[x_pos][y_pos-1].logic.connectedDown = True
                    karte[x_pos][y_pos].logic.connectedDown = True
                    karte[x_pos][y_pos+1].logic.connectedUp = True
                    karte[x_pos][y_pos-1].logicUpdate()            #Logik Update Oben
                    karte[x_pos][y_pos+1].logicUpdate()            #Logik Update Unten
                    if(karte[x_pos][y_pos-1].logic.way.firstTrainStation == None):                   #hinzufügen des Bahnhofs zur Strecke
                        karte[x_pos][y_pos-1].logic.way.firstTrainStation = karte[x_pos][y_pos]
                        karte[x_pos][y_pos-1].logic.way.firstRail.append(karte[x_pos][y_pos])
                        karte[x_pos][y_pos-1].logic.way.firstRail.append(None)
                    else:
                        karte[x_pos][y_pos-1].logic.way.secondTrainStation = karte[x_pos][y_pos]
                        karte[x_pos][y_pos-1].logic.way.firstRail.append(karte[x_pos][y_pos])
                        karte[x_pos][y_pos-1].logic.way.firstRail.append(None)
                    if(karte[x_pos][y_pos+1].logic.way.firstTrainStation == None):                   #hinzufügen des Bahnhofs zur Strecke
                        karte[x_pos][y_pos+1].logic.way.firstTrainStation = karte[x_pos][y_pos]
                        karte[x_pos][y_pos+1].logic.way.firstRail.append(karte[x_pos][y_pos])
                        karte[x_pos][y_pos+1].logic.way.secondRail.append(None)
                    else:
                        karte[x_pos][y_pos+1].logic.way.secondTrainStation = karte[x_pos][y_pos]
                        karte[x_pos][y_pos+1].logic.way.firstRail.append(karte[x_pos][y_pos])
                        karte[x_pos][y_pos+1].logic.way.secondRail.append(None)
                karte[x_pos][y_pos].logicUpdate()                   #Logik Update Bahnhof
            print(WayLogic.allWays[len(WayLogic.allWays)-1].firstRail)
            print(WayLogic.allWays[len(WayLogic.allWays)-1].secondRail)
            print(WayLogic.allWays[len(WayLogic.allWays)-1].firstTrainStation)
            print(WayLogic.allWays[len(WayLogic.allWays)-1].secondTrainStation)
        else:
            print('Kann Bahnhof hier nicht bauen!')

            print('die Tolle Build Funktion hat geklappt')
