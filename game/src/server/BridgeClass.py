from RailClass import RailLogic

class BridgeLogic():

    def __init__(self, pTile, pPlayer):
        self.x_Pos = pTile.getX()    
        self.y_Pos = pTile.getY()        
        self.tile = pTile
        self.connectedRight = False; #rechtsverbunden?
        self.connectedLeft = False #linksverbunden?
        self.connectedUp = False #obenverbunden?
        self.connectedDown = False #untenverbunden?
        self.player = pPlayer # Spieler X

    def getType(self):
        data = (self.connectedLeft, self.connectedRight, self.connectedUp, self.connectedDown)
        if(self.connectedLeft or self.connectedRight):            
            return 'BRIDGE_H'
        
        elif(self.connectedUp or self.connectedDown):            
            return 'BRIDGE_V'



    @staticmethod
    def checkConnectableRails(player, x_pos, y_pos, karte, riverType):
        print('Start Connectable Rails')
        railConnectableRight = False;   #Schiene rechts ist verbindbar?
        railConnectableLeft = False;    #Schiene links ist verbindbar?
        railConnectableUp = False;      #Schiene oben ist verbindbar?
        railConnectableDown = False;    #Schiene unten ist verbindbar?

        if(riverType == 4):                     #Verhindert, dass Brücke mit anderer Brücke verbunden wird.
            print('RIVER_V')
             #Rechts
            if(x_pos<299):                              #Wenn Rechts innerhalb der Karte liegt
                if(karte[x_pos+1][y_pos].isRail() or karte[x_pos+1][y_pos].isTrainStation() and karte[x_pos+1][y_pos].checkRotationStationVertical() == False): #Wenn Schiene oder horizontaler Bahnhof existiert
                    print('Wenn Schiene oder horizontaler Bahnhof existiert')
                    if(karte[x_pos+1][y_pos].logic.player == player): #Wenn Schiene oder Bahnhof zum selben Spieler gehoert
                        print('Wenn Schiene oder Bahnhof zum selben Spieler gehoert')
                        #Wenn Schiene oder Bahnhof nicht vollstaendig verbunden ist.
                        if(karte[x_pos+1][y_pos].logic.connectedRight + karte[x_pos+1][y_pos].logic.connectedLeft + karte[x_pos+1][y_pos].logic.connectedUp + karte[x_pos+1][y_pos].logic.connectedDown != 2):
                            print('Wenn Schiene oder Bahnhof nicht vollstaendig verbunden ist.')
                            railConnectableRight = True; #dann liegt rechts eine verbindbare Schiene
                            

            #Links
            if(x_pos>0):                                #Wenn Links innerhalb der Karte liegt
                print("Wenn  links innerhalb der Karte liegt")
                if(karte[x_pos-1][y_pos].isRail() or karte[x_pos-1][y_pos].isTrainStation() and karte[x_pos-1][y_pos].checkRotationStationVertical() == False): #Wenn Schiene oder horizontaler Bahnhof existiert
                    if(karte[x_pos-1][y_pos].logic.player == player): #Wenn Schiene oder Bahnhof zum selben Spieler gehoert
                        #Wenn Schiene oder Bahnhof nicht vollstaendig verbunden ist.
                        if(karte[x_pos-1][y_pos].logic.connectedRight + karte[x_pos-1][y_pos].logic.connectedLeft + karte[x_pos-1][y_pos].logic.connectedUp + karte[x_pos-1][y_pos].logic.connectedDown != 2):
                            railConnectableLeft = True;     #Dann liegt links eine verbindbare Schiene

        elif(riverType == 3):                   #Verhindert, dass Brücke mit anderer Brücke verbunden wird.
            print('RIVER_H')
            #Oben
            if(y_pos>0):                                #Wenn Oben innerhalb der Karte liegt
                print("Wenn oben innererhalb der Karte liegt")
                if(karte[x_pos][y_pos-1].isRail() or karte[x_pos][y_pos-1].isTrainStation() and karte[x_pos][y_pos-1].checkRotationStationVertical() == True): #Wenn Schiene oder vertikaler Bahnhof  existiert
                    print("Wenn Schiene oder vertikaler Bahnhof  existiert")
                    if(karte[x_pos][y_pos-1].logic.player == player): #Wenn Schiene oder Bahnhof zum selben Spieler gehoert
                        #Wenn Schiene oder Bahnhof nicht vollstaendig verbunden ist.
                        if(karte[x_pos][y_pos-1].logic.connectedRight + karte[x_pos][y_pos-1].logic.connectedLeft + karte[x_pos][y_pos-1].logic.connectedUp + karte[x_pos][y_pos-1].logic.connectedDown != 2):
                            railConnectableUp = True;            #Dann liegt Oben eine verbindbare Schiene

            #Unten
            if(y_pos<299):                              #Wenn Unten innerhalb der Karte liegt
                print("Wenn Unten innerhalb der Karte liegt")
                if(karte[x_pos][y_pos+1].isRail() or karte[x_pos][y_pos+1].isTrainStation() and karte[x_pos][y_pos+1].checkRotationStationVertical() == True):  #Wenn Schiene oder vertikaler Bahnhof existiert
                    if(karte[x_pos][y_pos+1].logic.player == player): #Wenn Schiene oder Bahnhof zum selben Spieler gehoert
                        #Wenn Schiene oder Bahnhof nicht vollstaendig verbunden ist.
                        if(karte[x_pos][y_pos+1].logic.connectedRight + karte[x_pos][y_pos+1].logic.connectedLeft + karte[x_pos][y_pos+1].logic.connectedUp + karte[x_pos][y_pos+1].logic.connectedDown != 2):
                            railConnectableDown = True                  #Dann liegt Unten eine verbindbare Schiene

        return railConnectableRight, railConnectableLeft,  railConnectableUp, railConnectableDown

    @staticmethod
    def build(x_pos,y_pos, pPlayer, karte, riverType):
        print("BridgeLogic.build @ start: ", x_pos, " ", y_pos);
        railConnectableRight, railConnectableLeft,  railConnectableUp, railConnectableDown = BridgeLogic.checkConnectableRails(pPlayer,x_pos ,y_pos , karte, riverType)
        print("BridgeLogic.build @ checkConnectableRails: ", RailLogic.checkConnectableRails(pPlayer,x_pos ,y_pos , karte))

        if(railConnectableUp + railConnectableDown + railConnectableRight + railConnectableLeft == 0): #Keine Schiene verbindbar.
            print("Brücken koennen nur an bestehendes Schienennetz gebaut werden")        
        
        
        elif (railConnectableUp + railConnectableDown + railConnectableRight + railConnectableLeft == 1): #1 Schienen vebindbar Unten,Oben, Rechts oder Links
            karte[x_pos][y_pos].initLogic(BridgeLogic) #Schiene wird gebaut.
            if(railConnectableRight == True):    #Schiene Rechts ist verbindbar                     
                karte[x_pos][y_pos].logic.connectedRight = True   #Schiene mit rechter Schiene verbinden
                karte[x_pos+1][y_pos].logic.connectedLeft = True  #Rechte Schiene mit Schiene verbinden 
                karte[x_pos+1][y_pos].logicUpdate()
                #if(karte[x_pos+1][y_pos].isTrainStation()):
                    #WayLogic.allWays.append(WayLogic)
                    #WayLogic.allWays[len(WayLogic.allWays)-1].firstRail.append(karte[x_pos][y_pos]) 



            if(railConnectableLeft == True):    #Schiene Links ist verbindbar.
                karte[x_pos][y_pos].logic.connectedLeft = True    #Schiene mit linker Schiene verbinden
                karte[x_pos-1][y_pos].logic.connectedRight = True #Linke Schiene mit Schiene verbinden
                karte[x_pos-1][y_pos].logicUpdate()


            if(railConnectableUp == True):      #Schiene Oben verbindbar.
                karte[x_pos][y_pos].logic.connectedUp = True  #Schiene mit oberer Schiene verbinden
                karte[x_pos][y_pos-1].logic.connectedDown = True     #Obere Schiene mit unterer Schiene verbinden
                karte[x_pos][y_pos-1].logicUpdate()


            if(railConnectableDown == True):    #Schiene Unten verbindbar.
                karte[x_pos][y_pos].logic.connectedDown = True    #Schiene mit unterer Schiene verbinden
                karte[x_pos][y_pos+1].logic.connectedUp = True      #Untere Schiene mit Schiene verbinden
                karte[x_pos][y_pos+1].logicUpdate()



            karte[x_pos][y_pos].logicUpdate()

        elif(railConnectableUp + railConnectableDown + railConnectableRight + railConnectableLeft == 2): #2 Schienen vebindbar Unten,Oben, Rechts oder Links
            karte[x_pos][y_pos].initLogic(BridgeLogic) #Schiene wird gebaut.
            if(railConnectableRight == True):    #Schiene Rechts ist verbindbar                     
                karte[x_pos][y_pos].logic.connectedRight = True   #Schiene mit rechter Schiene verbinden
                karte[x_pos+1][y_pos].logic.connectedLeft = True  #Rechte Schiene mit Schiene verbinden 
                karte[x_pos+1][y_pos].logicUpdate()



            if(railConnectableLeft == True):    #Schiene Links ist verbindbar.
                karte[x_pos][y_pos].logic.connectedLeft = True    #Schiene mit linker Schiene verbinden
                karte[x_pos-1][y_pos].logic.connectedRight = True #Linke Schiene mit Schiene verbinden
                karte[x_pos-1][y_pos].logicUpdate()


            if(railConnectableUp == True):      #Schiene Oben verbindbar.
                 karte[x_pos][y_pos].logic.connectedUp = True  #Schiene mit oberer Schiene verbinden
                 karte[x_pos][y_pos-1].logic.connectedDown = True     #Obere Schiene mit unterer Schiene verbinden
                 karte[x_pos][y_pos-1].logicUpdate()


            if(railConnectableDown == True):    #Schiene Unten verbindbar.
                karte[x_pos][y_pos].logic.connectedDown = True    #Schiene mit unterer Schiene verbinden
                karte[x_pos][y_pos+1].logic.connectedUp = True      #Untere Schiene mit Schiene verbinden
                karte[x_pos][y_pos+1].logicUpdate()



            karte[x_pos][y_pos].logicUpdate()

                            
