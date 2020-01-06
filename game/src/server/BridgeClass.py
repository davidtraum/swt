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
    def checkConnectableRails(player, x_Pos, y_Pos, karte, riverType):
        print('Start Connectable Rails')
        railConnectableRight = False;   #Schiene rechts ist verbindbar?
        railConnectableLeft = False;    #Schiene links ist verbindbar?
        railConnectableUp = False;      #Schiene oben ist verbindbar?
        railConnectableDown = False;    #Schiene unten ist verbindbar?

        if(riverType == 4):                     #Verhindert, dass Brücke mit anderer Brücke verbunden wird.
            print('RIVER_V')
             #Rechts
            if(x_Pos<299):                              #Wenn Rechts innerhalb der Karte liegt
                if(karte[x_Pos+1][y_Pos].isRail() or karte[x_Pos+1][y_Pos].isTrainStation() and karte[x_Pos+1][y_Pos].checkRotationStationVertical() == False): #Wenn Schiene oder horizontaler Bahnhof existiert
                    print('Wenn Schiene oder horizontaler Bahnhof existiert')
                    if(karte[x_Pos+1][y_Pos].logic.player == player): #Wenn Schiene oder Bahnhof zum selben Spieler gehoert
                        print('Wenn Schiene oder Bahnhof zum selben Spieler gehoert')
                        #Wenn Schiene oder Bahnhof nicht vollstaendig verbunden ist.
                        if(karte[x_Pos+1][y_Pos].logic.connectedRight + karte[x_Pos+1][y_Pos].logic.connectedLeft + karte[x_Pos+1][y_Pos].logic.connectedUp + karte[x_Pos+1][y_Pos].logic.connectedDown != 2):
                            print('Wenn Schiene oder Bahnhof nicht vollstaendig verbunden ist.')
                            railConnectableRight = True; #dann liegt rechts eine verbindbare Schiene
                            

            #Links
            if(x_Pos>0):                                #Wenn Links innerhalb der Karte liegt
                print("Wenn  links innerhalb der Karte liegt")
                if(karte[x_Pos-1][y_Pos].isRail() or karte[x_Pos-1][y_Pos].isTrainStation() and karte[x_Pos-1][y_Pos].checkRotationStationVertical() == False): #Wenn Schiene oder horizontaler Bahnhof existiert
                    if(karte[x_Pos-1][y_Pos].logic.player == player): #Wenn Schiene oder Bahnhof zum selben Spieler gehoert
                        #Wenn Schiene oder Bahnhof nicht vollstaendig verbunden ist.
                        if(karte[x_Pos-1][y_Pos].logic.connectedRight + karte[x_Pos-1][y_Pos].logic.connectedLeft + karte[x_Pos-1][y_Pos].logic.connectedUp + karte[x_Pos-1][y_Pos].logic.connectedDown != 2):
                            railConnectableLeft = True;     #Dann liegt links eine verbindbare Schiene

        elif(riverType == 3):                   #Verhindert, dass Brücke mit anderer Brücke verbunden wird.
            print('RIVER_H')
            #Oben
            if(y_Pos>0):                                #Wenn Oben innerhalb der Karte liegt
                print("Wenn oben innererhalb der Karte liegt")
                if(karte[x_Pos][y_Pos-1].isRail() or karte[x_Pos][y_Pos-1].isTrainStation() and karte[x_Pos][y_Pos-1].checkRotationStationVertical() == True): #Wenn Schiene oder vertikaler Bahnhof  existiert
                    print("Wenn Schiene oder vertikaler Bahnhof  existiert")
                    if(karte[x_Pos][y_Pos-1].logic.player == player): #Wenn Schiene oder Bahnhof zum selben Spieler gehoert
                        #Wenn Schiene oder Bahnhof nicht vollstaendig verbunden ist.
                        if(karte[x_Pos][y_Pos-1].logic.connectedRight + karte[x_Pos][y_Pos-1].logic.connectedLeft + karte[x_Pos][y_Pos-1].logic.connectedUp + karte[x_Pos][y_Pos-1].logic.connectedDown != 2):
                            railConnectableUp = True;            #Dann liegt Oben eine verbindbare Schiene

            #Unten
            if(y_Pos<299):                              #Wenn Unten innerhalb der Karte liegt
                print("Wenn Unten innerhalb der Karte liegt")
                if(karte[x_Pos][y_Pos+1].isRail() or karte[x_Pos][y_Pos+1].isTrainStation() and karte[x_Pos][y_Pos+1].checkRotationStationVertical() == True):  #Wenn Schiene oder vertikaler Bahnhof existiert
                    if(karte[x_Pos][y_Pos+1].logic.player == player): #Wenn Schiene oder Bahnhof zum selben Spieler gehoert
                        #Wenn Schiene oder Bahnhof nicht vollstaendig verbunden ist.
                        if(karte[x_Pos][y_Pos+1].logic.connectedRight + karte[x_Pos][y_Pos+1].logic.connectedLeft + karte[x_Pos][y_Pos+1].logic.connectedUp + karte[x_Pos][y_Pos+1].logic.connectedDown != 2):
                            railConnectableDown = True                  #Dann liegt Unten eine verbindbare Schiene

        return railConnectableRight, railConnectableLeft,  railConnectableUp, railConnectableDown

    @staticmethod
    def build(x_Pos,y_Pos, pPlayer, karte, riverType):
        print("BridgeLogic.build @ start: ", x_Pos, " ", y_Pos);
        railConnectableRight, railConnectableLeft,  railConnectableUp, railConnectableDown = BridgeLogic.checkConnectableRails(pPlayer,x_Pos ,y_Pos , karte, riverType)
        print("BridgeLogic.build @ checkConnectableRails: ", RailLogic.checkConnectableRails(pPlayer,x_Pos ,y_Pos , karte))

        if(railConnectableUp + railConnectableDown + railConnectableRight + railConnectableLeft == 0): #Keine Schiene verbindbar.
            print("Brücken koennen nur an bestehendes Schienennetz gebaut werden")        
        
        
        elif (railConnectableUp + railConnectableDown + railConnectableRight + railConnectableLeft == 1): #1 Schienen vebindbar Unten,Oben, Rechts oder Links
            karte[x_Pos][y_Pos].initLogic(BridgeLogic) #Schiene wird gebaut.
            if(railConnectableRight == True):    #Schiene Rechts ist verbindbar                     
                karte[x_Pos][y_Pos].logic.connectedRight = True   #Schiene mit rechter Schiene verbinden
                karte[x_Pos+1][y_Pos].logic.connectedLeft = True  #Rechte Schiene mit Schiene verbinden 
                karte[x_Pos+1][y_Pos].logicUpdate()
                if(karte[x_Pos+1][y_Pos].isTrainStation()):                                             #wenn Rechts ein Bahnhof,
                    WayLogic.allWays.append(WayLogic(None))                                             #dann füge neue Strecke hinzu
                    karte[x_Pos][y_Pos].logic.way = WayLogic.allWays[len(WayLogic.allWays)-1]           #vermerke in Schiene zu welcher Strecke sie gehört
                    WayLogic.allWays[len(WayLogic.allWays)-1].firstRail.append(karte[x_Pos+1][y_Pos])   #1.Bahnhof wird Strecke hinzugefügt
                    WayLogic.allWays[len(WayLogic.allWays)-1].secondRail.append(None)                   #2. Gleis des Bahnhofs wird Strecke hinzugefügt(bis jetzt immer None)
                    WayLogic.allWays[len(WayLogic.allWays)-1].firstRail.append(karte[x_Pos][y_Pos])     #erstem Gleis der Strecke wird Schiene hinzugefügt
                    WayLogic.allWays[len(WayLogic.allWays)-1].secondRail.append(None)                   #zweitem Gleis der Strecke wird nichts hinzugefügt
                    print(WayLogic.allWays[len(WayLogic.allWays)-1].firstRail, WayLogic.allWays[len(WayLogic.allWays)-1].secondRail)
                else:                                                                               #Wenn Rechts eine Schiene ist
                                                                                                          #Wenn Rechts eine Schiene ist
                    if(karte[x_Pos+1][y_Pos].logic.way.firstRail.index(karte[x_Pos+1][y_Pos]) != 0):         #Wenn schiene nicht die erste ist
                        karte[x_Pos+1][y_Pos].logic.way.firstRail.append(karte[x_Pos][y_Pos])               #erstem Gleis der Strecke wird Schiene hinzugefügt
                        karte[x_Pos+1][y_Pos].logic.way.secondRail.append(None)                             #zweitem Gleis der Strecke wird nichts hinzugefügt
                        karte[x_Pos][y_Pos].logic.way = karte[x_Pos+1][y_Pos].logic.way                     #vermerke in Schiene, dass sie zurselben Strecke wie die rechte Schiene gehört
                    else:                    
                        karte[x_Pos+1][y_Pos].logic.way.firstRail.insert(0, karte[x_Pos][y_Pos])               #erstem Gleis der Strecke wird Schiene hinzugefügt
                        karte[x_Pos+1][y_Pos].logic.way.secondRail.insert(0, None)                             #zweitem Gleis der Strecke wird nichts hinzugefügt
                        karte[x_Pos][y_Pos].logic.way = karte[x_Pos+1][y_Pos].logic.way 



            if(railConnectableLeft == True):    #Schiene Links ist verbindbar.
                karte[x_Pos][y_Pos].logic.connectedLeft = True    #Schiene mit linker Schiene verbinden
                karte[x_Pos-1][y_Pos].logic.connectedRight = True #Linke Schiene mit Schiene verbinden
                karte[x_Pos-1][y_Pos].logicUpdate()
                if(karte[x_Pos-1][y_Pos].isTrainStation()):                                             #wenn Links ein Bahnhof,
                    WayLogic.allWays.append(WayLogic(None))                                             #dann füge neue Strecke hinzu
                    karte[x_Pos][y_Pos].logic.way = WayLogic.allWays[len(WayLogic.allWays)-1]           #vermerke in Schiene zu welcher Strecke sie gehört
                    WayLogic.allWays[len(WayLogic.allWays)-1].firstRail.append(karte[x_Pos-1][y_Pos])   #1.Bahnhof wird Strecke hinzugefügt
                    WayLogic.allWays[len(WayLogic.allWays)-1].secondRail.append(None)                   #2. Gleis des Bahnhofs wird Strecke hinzugefügt(bis jetzt immer None)
                    WayLogic.allWays[len(WayLogic.allWays)-1].firstRail.append(karte[x_Pos][y_Pos])     #erstem Gleis der Strecke wird Schiene hinzugefügt
                    WayLogic.allWays[len(WayLogic.allWays)-1].secondRail.append(None)                   #zweitem Gleis der Strecke wird nichts hinzugefügt
                    print(WayLogic.allWays[len(WayLogic.allWays)-1].firstRail, WayLogic.allWays[len(WayLogic.allWays)-1].secondRail)
                else:                                                                                   #Wenn Links eine Schiene ist
                    if(karte[x_Pos-1][y_Pos].logic.way.firstRail.index(karte[x_Pos-1][y_Pos]) != 0):         #Wenn schiene nicht die erste ist
                        karte[x_Pos-1][y_Pos].logic.way.firstRail.append(karte[x_Pos][y_Pos])               #erstem Gleis der Strecke wird Schiene hinzugefügt
                        karte[x_Pos-1][y_Pos].logic.way.secondRail.append(None)                             #zweitem Gleis der Strecke wird nichts hinzugefügt
                        karte[x_Pos][y_Pos].logic.way = karte[x_Pos-1][y_Pos].logic.way                     #vermerke in Schiene, dass sie zurselben Strecke wie die rechte Schiene gehört
                    else:                    
                        karte[x_Pos-1][y_Pos].logic.way.firstRail.insert(0, karte[x_Pos][y_Pos])               #erstem Gleis der Strecke wird Schiene hinzugefügt
                        karte[x_Pos-1][y_Pos].logic.way.secondRail.insert(0, None)                             #zweitem Gleis der Strecke wird nichts hinzugefügt
                        karte[x_Pos][y_Pos].logic.way = karte[x_Pos-1][y_Pos].logic.way                     #vermerke in Schiene, dass sie zurselben Strecke wie die rechte Schiene gehört


            if(railConnectableUp == True):      #Schiene Oben verbindbar.
                karte[x_Pos][y_Pos].logic.connectedUp = True  #Schiene mit oberer Schiene verbinden
                karte[x_Pos][y_Pos-1].logic.connectedDown = True     #Obere Schiene mit unterer Schiene verbinden
                karte[x_Pos][y_Pos-1].logicUpdate()
                if(karte[x_Pos][y_Pos-1].isTrainStation()):                                             #wenn Oben ein Bahnhof,
                    WayLogic.allWays.append(WayLogic(None))                                             #dann füge neue Strecke hinzu
                    karte[x_Pos][y_Pos].logic.way = WayLogic.allWays[len(WayLogic.allWays)-1]           #vermerke in Schiene zu welcher Strecke sie gehört
                    WayLogic.allWays[len(WayLogic.allWays)-1].firstRail.append(karte[x_Pos][y_Pos-1])   #1.Bahnhof wird Strecke hinzugefügt
                    WayLogic.allWays[len(WayLogic.allWays)-1].secondRail.append(None)                   #2. Gleis des Bahnhofs wird Strecke hinzugefügt(bis jetzt immer None)
                    WayLogic.allWays[len(WayLogic.allWays)-1].firstRail.append(karte[x_Pos][y_Pos])     #erstem Gleis der Strecke wird Schiene hinzugefügt
                    WayLogic.allWays[len(WayLogic.allWays)-1].secondRail.append(None)                   #zweitem Gleis der Strecke wird nichts hinzugefügt
                    print(WayLogic.allWays[len(WayLogic.allWays)-1].firstRail, WayLogic.allWays[len(WayLogic.allWays)-1].secondRail)
                else:                                                                                   #Wenn Oben eine Schiene ist
                    if(karte[x_Pos][y_Pos-1].logic.way.firstRail.index(karte[x_Pos][y_Pos-1]) != 0):         #Wenn schiene nicht die erste ist
                        karte[x_Pos][y_Pos-1].logic.way.firstRail.append(karte[x_Pos][y_Pos])               #erstem Gleis der Strecke wird Schiene hinzugefügt
                        karte[x_Pos][y_Pos-1].logic.way.secondRail.append(None)                             #zweitem Gleis der Strecke wird nichts hinzugefügt
                        karte[x_Pos][y_Pos].logic.way = karte[x_Pos][y_Pos-1].logic.way                     #vermerke in Schiene, dass sie zurselben Strecke wie die rechte Schiene gehört
                    else:                    
                        karte[x_Pos][y_Pos-1].logic.way.firstRail.insert(0, karte[x_Pos][y_Pos])               #erstem Gleis der Strecke wird Schiene hinzugefügt
                        karte[x_Pos][y_Pos-1].logic.way.secondRail.insert(0, None)                             #zweitem Gleis der Strecke wird nichts hinzugefügt
                        karte[x_Pos][y_Pos].logic.way = karte[x_Pos][y_Pos-1].logic.way 



            if(railConnectableDown == True):    #Schiene Unten verbindbar.
                karte[x_Pos][y_Pos].logic.connectedDown = True    #Schiene mit unterer Schiene verbinden
                karte[x_Pos][y_Pos+1].logic.connectedUp = True      #Untere Schiene mit Schiene verbinden
                karte[x_Pos][y_Pos+1].logicUpdate()
                if(karte[x_Pos][y_Pos+1].isTrainStation()):                                             #wenn Unten ein Bahnhof,
                    WayLogic.allWays.append(WayLogic(None))                                             #dann füge neue Strecke hinzu
                    karte[x_Pos][y_Pos].logic.way = WayLogic.allWays[len(WayLogic.allWays)-1]           #vermerke in Schiene zu welcher Strecke sie gehört
                    WayLogic.allWays[len(WayLogic.allWays)-1].firstRail.append(karte[x_Pos][y_Pos+1])   #1.Bahnhof wird Strecke hinzugefügt
                    WayLogic.allWays[len(WayLogic.allWays)-1].secondRail.append(None)                   #2. Gleis des Bahnhofs wird Strecke hinzugefügt(bis jetzt immer None)
                    WayLogic.allWays[len(WayLogic.allWays)-1].firstRail.append(karte[x_Pos][y_Pos])     #erstem Gleis der Strecke wird Schiene hinzugefügt
                    WayLogic.allWays[len(WayLogic.allWays)-1].secondRail.append(None)                   #zweitem Gleis der Strecke wird nichts hinzugefügt
                    print(WayLogic.allWays[len(WayLogic.allWays)-1].firstRail, WayLogic.allWays[len(WayLogic.allWays)-1].secondRail)
                else:                                                                                   #Wenn Unten eine Schiene ist
                    if(karte[x_Pos][y_Pos+1].logic.way.firstRail.index(karte[x_Pos][y_Pos+1]) != 0):         #Wenn schiene nicht die erste ist
                        karte[x_Pos][y_Pos+1].logic.way.firstRail.append(karte[x_Pos][y_Pos])               #erstem Gleis der Strecke wird Schiene hinzugefügt
                        karte[x_Pos][y_Pos+1].logic.way.secondRail.append(None)                             #zweitem Gleis der Strecke wird nichts hinzugefügt
                        karte[x_Pos][y_Pos].logic.way = karte[x_Pos][y_Pos+1].logic.way                     #vermerke in Schiene, dass sie zurselben Strecke wie die rechte Schiene gehört
                    else:                    
                        karte[x_Pos][y_Pos+1].logic.way.firstRail.insert(0, karte[x_Pos][y_Pos])               #erstem Gleis der Strecke wird Schiene hinzugefügt
                        karte[x_Pos][y_Pos+1].logic.way.secondRail.insert(0, None)                             #zweitem Gleis der Strecke wird nichts hinzugefügt
                        karte[x_Pos][y_Pos].logic.way = karte[x_Pos][y_Pos+1].logic.way 



            karte[x_Pos][y_Pos].logicUpdate()

        elif(railConnectableUp + railConnectableDown + railConnectableRight + railConnectableLeft == 2): #2 Schienen vebindbar Unten,Oben, Rechts oder Links
            karte[x_Pos][y_Pos].initLogic(BridgeLogic) #Schiene wird gebaut.
            if(railConnectableRight == True):    #Schiene Rechts ist verbindbar                     
                karte[x_Pos][y_Pos].logic.connectedRight = True   #Schiene mit rechter Schiene verbinden
                karte[x_Pos+1][y_Pos].logic.connectedLeft = True  #Rechte Schiene mit Schiene verbinden 
                karte[x_Pos+1][y_Pos].logicUpdate()



            if(railConnectableLeft == True):    #Schiene Links ist verbindbar.
                karte[x_Pos][y_Pos].logic.connectedLeft = True    #Schiene mit linker Schiene verbinden
                karte[x_Pos-1][y_Pos].logic.connectedRight = True #Linke Schiene mit Schiene verbinden
                karte[x_Pos-1][y_Pos].logicUpdate()


            if(railConnectableUp == True):      #Schiene Oben verbindbar.
                 karte[x_Pos][y_Pos].logic.connectedUp = True  #Schiene mit oberer Schiene verbinden
                 karte[x_Pos][y_Pos-1].logic.connectedDown = True     #Obere Schiene mit unterer Schiene verbinden
                 karte[x_Pos][y_Pos-1].logicUpdate()


            if(railConnectableDown == True):    #Schiene Unten verbindbar.
                karte[x_Pos][y_Pos].logic.connectedDown = True    #Schiene mit unterer Schiene verbinden
                karte[x_Pos][y_Pos+1].logic.connectedUp = True      #Untere Schiene mit Schiene verbinden
                karte[x_Pos][y_Pos+1].logicUpdate()



            karte[x_Pos][y_Pos].logicUpdate()

    def remove(x_Pos,y_Pos, pPlayer, karte): 
        if(karte[x_Pos][y_Pos].player == pPlayer):
            if(self.connectedRight + self.connectedLeft + self.connectedUp +self.connectedDown == 1):
                karte[x_Pos][y_Pos].setType('GRASS')    #Maptile wird wieder auf Gras gesetzt
                if(self.connectedRight == True):        #entfernt Verbindungen von anderen Schienen
                    karte[x_Pos+1][y_Pos].logic.connectedLeft = False
                if(self.connectedLeft == True):
                    karte[x_Pos-1][y_Pos].logic.connectedRight = False
                if(self.connectedUp == True):
                    karte[x_Pos][y_Pos-1].logic.connectedDown = False
                if(self.connectedDown == True):
                    karte[x_Pos][y_Pos+1].logic.connectedUp = False                
                tmp = karte[x_Pos][y_Pos].logic.way.firstRail.index(karte[x_Pos][y_Pos])    #entfernt Gleis aus Strecke
                del karte[x_Pos][y_Pos].logic.way.firstRail[tmp]            
                del karte[x_Pos][y_Pos].logic.way.secondRail[tmp]                          
                karte[x_Pos][y_Pos].logic = None        #setzt Logic Objekt auf None

                            
