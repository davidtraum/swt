from GameLogicObject import GameLogicObject
import types


class RailLogic(GameLogicObject):

    def __init__(self, px_Pos, py_Pos, pPlayer):
        self.x_Pos = px_Pos;    
        self.y_Pos = py_Pos;        
        self.connectedRight = False; #rechtsverbunden?
        self.connectedLeft = False #linksverbunden?
        self.connectedUp = False #obenverbunden?
        self.connectedDown = False #untenverbunden?
        self.player = pPlayer # Spieler X

    def getConnections(self):
        return (str(int(self.connectedRight)) + str(int(self.connectedLeft)) + str(int(self.connectedUp)) + str(int(self.connectedDown)))
        

    @staticmethod
    def checkconnectableRails(player, x_pos, y_pos, karte):
        railConnectableRight = False;   #Schiene rechts ist verbindbar?
        railConnectableLeft = False;    #Schiene links ist verbindbar?
        railConnectableUp = False;      #Schiene oben ist verbindbar?
        railConnectableDown = False;    #Schiene unten ist verbindbar?

        



        #Rechts
        if(x_pos<299):                              #Wenn Rechts innerhalb der Karte liegt
            if(type(karte[x_pos+1][y_pos]) == RailLogic): #Wenn Schiene existiert
                if(karte[x_pos+1][y_pos].player == player): #Wenn Schiene zum selben Spieler gehört
                    #Wenn Schiene nicht vollständig verbunden ist.
                    if(karte[x_pos+1][y_pos].connectedRight + karte[x_pos+1][y_pos].connectedLeft + karte[x_pos+1][y_pos].connectedUp + karte[x_pos+1][y_pos].connectedUp != 2):
                        railConnectableRight = True; #dann liegt rechts eine verbindbare Schiene

        #Links
        if(x_pos>0):                                #Wenn Links innerhalb der Karte liegt
            if(type(karte[x_pos-1][y_pos]) == RailLogic): #Wenn Schiene existiert
                if(karte[x_pos-1][y_pos].player == player): #Wenn Schiene zum selben Spieler gehört
                    #Wenn Schiene nicht vollständig verbunden ist.                    
                    if(karte[x_pos-1][y_pos].connectedRight + karte[x_pos-1][y_pos].connectedLeft + karte[x_pos-1][y_pos].connectedUp + karte[x_pos-1][y_pos].connectedUp != 2):
                        railConnectableLeft = True;     #Dann liegt links eine verbindbare Schiene
                        
        
        #Oben
        if(y_pos>0):                                #Wenn Oben innerhalb der Karte liegt
            if(type(karte[x_pos][y_pos-1]) == RailLogic): #Wenn Schiene existiert
                if(karte[x_pos][y_pos-1].player == player): #Wenn Schiene zum selben Spieler gehört
                    #Wenn Schiene nicht vollständig verbunden ist.
                    if(karte[x_pos][y_pos-1].connectedRight + karte[x_pos][y_pos-1].connectedLeft + karte[x_pos][y_pos-1].connectedUp + karte[x_pos][y_pos-1].connectedUp != 2):
                        railConnectableUp = True;            #Dann liegt Oben eine verbindbare Schiene

        #Unten
        if(y_pos<299):                              #Wenn Unten innerhalb der Karte liegt
            if(type(karte[x_pos][y_pos+1]) == RailLogic): #Wenn Schiene existiert
                if(karte[x_pos][y_pos+1].player == player): #Wenn Schiene zum selben Spieler gehört
                    #Wenn Schiene nicht vollständig verbunden ist.
                    if(karte[x_pos][y_pos+1].connectedRight + karte[x_pos][y_pos+1].connectedLeft + karte[x_pos][y_pos+1].connectedUp + karte[x_pos][y_pos+1].connectedUp != 2):
                        railExistsDown = True;                  #Dann liegt Unten eine verbindbare Schiene

       
                
        return railConnectableRight, railConnectableLeft,  railConnectableUp, railConnectableDown  

    @staticmethod
    def build(x_pos,y_pos, pPlayer, karte):

        railConnectableRight, railConnectableLeft,  railConnectableUp, railConnectableDown = RailLogic.checkconnectableRails(pPlayer,x_pos ,y_pos , karte)
        print(railConnectableRight, railConnectableLeft,  railConnectableUp, railConnectableDown)  #zum Testen
        if(railConnectableUp + railConnectableDown + railConnectableRight + railConnectableLeft == 0): #Keine Schiene verbindbar.
            print("Schienen können nur an bestehendes Schienennetz gebaut werden")        
        
        
        elif(1 <= railConnectableUp + railConnectableDown + railConnectableRight + railConnectableLeft <= 2): #1-2 Schienen vebindbar Unten,Oben, Rechts oder Links

            karte[x_pos][y_pos] = RailLogic(x_pos, y_pos, pPlayer) #Schiene wird gebaut.
            
            if(railConnectableRight == True):    #Schiene Rechts ist verbindbar                     
                karte[x_pos][y_pos].connectedRight = True   #Schiene mit rechter Schiene verbinden
                karte[x_pos+1][y_pos].connectedLeft = True  #Rechte Schiene mit Schiene verbinden                    
    

            if(railConnectableLeft == True):    #Schiene Links ist verbindbar.
                karte[x_pos][y_pos].connectedLeft = True    #Schiene mit linker Schiene verbinden
                karte[x_pos-1][y_pos].connectedRight = True #Linke Schiene mit Schiene verbinden

            if(railConnectableUp == True):      #Schiene Oben verbindbar.
                karte[x_pos][y_pos].connectedUp = True  #Schiene mit oberer Schiene verbinden
                karte[x_pos][y_pos-1].connectedDown = True     #Obere Schiene mit unterer Schiene verbinden

            if(railConnectableDown == True):    #Schiene Unten verbindbar.
                karte[x_pos][y_pos].connectedDown = True    #Schiene mit unterer Schiene verbinden
                karte[x_pos][y_pos+1].connectedUp = True      #Untere Schiene mit Schiene verbinden

        else:
            print("Spielerabfrage") #z.B. mit vier Richtungen, die ersten beiden(anklickbaren) die geklickt werden bestimmen die Kurve
                




        
        

