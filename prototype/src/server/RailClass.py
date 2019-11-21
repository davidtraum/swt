import types

class RailLogic:

    def __init__(self, pTile, pPlayer):
        self.x_Pos = pTile.getX()    
        self.y_Pos = pTile.getY()        
        self.tile = pTile
        self.connectedRight = False; #rechtsverbunden?
        self.connectedLeft = False #linksverbunden?
        self.connectedUp = False #obenverbunden?
        self.connectedDown = False #untenverbunden?
        self.player = pPlayer # Spieler X

    def getConnections(self):
        return (str(int(self.connectedRight)) + str(int(self.connectedLeft)) + str(int(self.connectedUp)) + str(int(self.connectedDown)))
        
    def getRailType(self):
        return 'RAIL_H'

    @staticmethod
    def checkConnectableRails(player, x_pos, y_pos, karte):
        railConnectableRight = False;   #Schiene rechts ist verbindbar?
        railConnectableLeft = False;    #Schiene links ist verbindbar?
        railConnectableUp = False;      #Schiene oben ist verbindbar?
        railConnectableDown = False;    #Schiene unten ist verbindbar?

        



        #Rechts
        if(x_pos<299):                              #Wenn Rechts innerhalb der Karte liegt
            if(karte[x_pos+1][y_pos].isRail()): #Wenn Schiene existiert
                if(karte[x_pos+1][y_pos].player == player): #Wenn Schiene zum selben Spieler gehoert
                    #Wenn Schiene nicht vollstaendig verbunden ist.
                    if(karte[x_pos+1][y_pos].logic.connectedRight + karte[x_pos+1][y_pos].logic.connectedLeft + karte[x_pos+1][y_pos].logic.connectedUp + karte[x_pos+1][y_pos].logic.connectedUp != 2):
                        railConnectableRight = True; #dann liegt rechts eine verbindbare Schiene

        #Links
        if(x_pos>0):                                #Wenn Links innerhalb der Karte liegt
            if(karte[x_pos-1][y_pos].isRail()): #Wenn Schiene existiert
                if(karte[x_pos-1][y_pos].logic.player == player): #Wenn Schiene zum selben Spieler gehoert
                    #Wenn Schiene nicht vollstaendig verbunden ist.                    
                    if(karte[x_pos-1][y_pos].logic.connectedRight + karte[x_pos-1][y_pos].logic.connectedLeft + karte[x_pos-1][y_pos].logic.connectedUp + karte[x_pos-1][y_pos].logic.connectedUp != 2):
                        railConnectableLeft = True;     #Dann liegt links eine verbindbare Schiene
                        
        
        #Oben
        if(y_pos>0):                                #Wenn Oben innerhalb der Karte liegt
            if(karte[x_pos][y_pos-1].isRail()): #Wenn Schiene existiert
                if(karte[x_pos][y_pos-1].logic.player == player): #Wenn Schiene zum selben Spieler gehoert
                    #Wenn Schiene nicht vollstaendig verbunden ist.
                    if(karte[x_pos][y_pos-1].logic.connectedRight + karte[x_pos][y_pos-1].logic.connectedLeft + karte[x_pos][y_pos-1].logic.connectedUp + karte[x_pos][y_pos-1].logic.connectedUp != 2):
                        railConnectableUp = True;            #Dann liegt Oben eine verbindbare Schiene

        #Unten
        if(y_pos<299):                              #Wenn Unten innerhalb der Karte liegt
            if(karte[x_pos][y_pos+1].isRail()): #Wenn Schiene existiert
                if(karte[x_pos][y_pos+1].logic.player == player): #Wenn Schiene zum selben Spieler gehoert
                    #Wenn Schiene nicht vollstaendig verbunden ist.
                    if(karte[x_pos][y_pos+1].logic.connectedRight + karte[x_pos][y_pos+1].logic.connectedLeft + karte[x_pos][y_pos+1].connectedUp + karte[x_pos][y_pos+1].logic.connectedUp != 2):
                        railConnectableDown = True                  #Dann liegt Unten eine verbindbare Schiene

       
                
        return railConnectableRight, railConnectableLeft,  railConnectableUp, railConnectableDown  

    @staticmethod
    def build(x_pos,y_pos, pPlayer, karte):
        changed = None
        railConnectableRight, railConnectableLeft,  railConnectableUp, railConnectableDown = RailLogic.checkConnectableRails(pPlayer,x_pos ,y_pos , karte)
        print(railConnectableRight, railConnectableLeft,  railConnectableUp, railConnectableDown)  #zum Testen
        if(railConnectableUp + railConnectableDown + railConnectableRight + railConnectableLeft == 0): #Keine Schiene verbindbar.
            print("Schienen koennen nur an bestehendes Schienennetz gebaut werden")        
        
        
        elif(1 <= railConnectableUp + railConnectableDown + railConnectableRight + railConnectableLeft <= 2): #1-2 Schienen vebindbar Unten,Oben, Rechts oder Links
            changed = []
            karte[x_pos][y_pos].initLogic(RailLogic) #Schiene wird gebaut.
            changed.append( karte[x_pos][y_pos] )
            if(railConnectableRight == True):    #Schiene Rechts ist verbindbar                     
                karte[x_pos][y_pos].logic.connectedRight = True   #Schiene mit rechter Schiene verbinden
                karte[x_pos+1][y_pos].logic.connectedLeft = True  #Rechte Schiene mit Schiene verbinden   
                changed.append( karte[x_pos+1][y_pos] );                 


            if(railConnectableLeft == True):    #Schiene Links ist verbindbar.
                karte[x_pos][y_pos].logic.connectedLeft = True    #Schiene mit linker Schiene verbinden
                karte[x_pos-1][y_pos].logic.connectedRight = True #Linke Schiene mit Schiene verbinden
                changed.append( karte[x_pos-1][y_pos] ); 

            if(railConnectableUp == True):      #Schiene Oben verbindbar.
                karte[x_pos][y_pos].logic.connectedUp = True  #Schiene mit oberer Schiene verbinden
                karte[x_pos][y_pos-1].logic.connectedDown = True     #Obere Schiene mit unterer Schiene verbinden
                changed.append( karte[x_pos][y_pos-1] ); 

            if(railConnectableDown == True):    #Schiene Unten verbindbar.
                karte[x_pos][y_pos].logic.connectedDown = True    #Schiene mit unterer Schiene verbinden
                karte[x_pos][y_pos+1].logic.connectedUp = True      #Untere Schiene mit Schiene verbinden
                changed.append( karte[x_pos][y_pos+1] ); 

        else:
            print("Spielerabfrage") #z.B. mit vier Richtungen, die ersten beiden(anklickbaren) die geklickt werden bestimmen die Kurve

        return changed;
                




        
        

