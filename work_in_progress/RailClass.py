from GameLogicObject import GameLogicObject


class RailLogic(GameLogicObject):

    def __init__(self, world, px_Pos, py_Pos, typeOfRail):
        self.x_Pos = px_Pos;
        self.y_Pos = py_Pos;        
        self.Direction = 0; #0 ist horizontal #1 ist vertikal
        
        #Art der Kurven/Geraden muss gespeichert werden für checkRails
        world.data[px_Pos][py_Pos].setType(typeOfRail);

    @staticmethod
    def _checkRails(self, x_Pos, y_Pos, karte):
        railExistsUp = 0; 
        railExistsDown = 0;
        railExistsLeft = 0;
        railExistsRight = 0;
        railExistsUpLeft = 0;
        railExistsUpRight = 0;
        railExistsDownLeft = 0;
        railExistsDownRight = 0;



        #Rechts
        if (karte[x_Pos+1][y_Pos].getType() == 9):
            railExistsRight = 9;
        if (karte[x_Pos+1][y_Pos].getType() == 10):
            railExistsRight = 10;
        if (karte[x_Pos+1][y_Pos].getType() == 11):
            railExistsRight = 11;
        if (karte[x_Pos+1][y_Pos].getType() == 12):
            railExistsRight = 12;
        if (karte[x_Pos+1][y_Pos].getType() == 13):
            railExistsRight = 13;
        if (karte[x_Pos+1][y_Pos].getType() == 14):
            railExistsRight = 14;

        #Links
        if (karte[x_Pos-1][y_Pos].getType() == 9):
            railExistsLeft = 9;
        if (karte[x_Pos-1][y_Pos].getType() == 10):
            railExistsLeft = 10;
        if (karte[x_Pos-1][y_Pos].getType() == 11):
            railExistsLeft = 11;
        if (karte[x_Pos-1][y_Pos].getType() == 12):
            railExistsLeft = 12;
        if (karte[x_Pos-1][y_Pos].getType() == 13):
            railExistsLeft = 13;
        if (karte[x_Pos-1][y_Pos].getType() == 14):
            railExistsLeft = 14;
        
        #Oben
        if (karte[x_Pos][y_Pos-1].getType() == 9):
            railExistsUp = 9;
        if (karte[x_Pos][y_Pos-1].getType() == 10):
            railExistsUp = 10;
        if (karte[x_Pos][y_Pos-1].getType() == 11):
            railExistsUp = 11;
        if (karte[x_Pos][y_Pos-1].getType() == 12):
            railExistsUp = 12;
        if (karte[x_Pos][y_Pos-1].getType() == 13):
            railExistsUp = 13;
        if (karte[x_Pos][y_Pos-1].getType() == 14):
            railExistsUp = 14;

        #Unten
        if (karte[x_Pos][y_Pos+1].getType() == 9):
            railExistsDown = 9;
        if (karte[x_Pos][y_Pos+1].getType() == 10):
            railExistsDown = 10;
        if (karte[x_Pos][y_Pos+1].getType() == 11):
            railExistsDown = 11;
        if (karte[x_Pos][y_Pos+1].getType() == 12):
            railExistsDown = 12;
        if (karte[x_Pos][y_Pos+1].getType() == 13):
            railExistsDown = 13;
        if (karte[x_Pos][y_Pos+1].getType() == 14):
            railExistsDown = 14;

        #ObenRechts

        if (karte[x_Pos+1][y_Pos-1].getType() == 9):
            railExistsUpRight = 9;
        if (karte[x_Pos+1][y_Pos-1].getType() == 10):
            railExistsUpRight = 10;
        if (karte[x_Pos+1][y_Pos-1].getType() == 11):
            railExistsUpRight = 11;
        if (karte[x_Pos+1][y_Pos-1].getType() == 12):
            railExistsUpRight = 12;
        if (karte[x_Pos+1][y_Pos-1].getType() == 13):
            railExistsUpRight = 13;
        if (karte[x_Pos+1][y_Pos-1].getType() == 14):
            railExistsUpRight = 14;

        #ObenLinks

        if (karte[x_Pos-1][y_Pos-1].getType() == 9):
            railExistsUpLeft = 9;
        if (karte[x_Pos-1][y_Pos-1].getType() == 10):
            railExistsUpLeft = 10;
        if (karte[x_Pos-1][y_Pos-1].getType() == 11):
            railExistsUpLeft = 11;
        if (karte[x_Pos-1][y_Pos-1].getType() == 12):
            railExistsUpLeft = 12;
        if (karte[x_Pos-1][y_Pos-1].getType() == 13):
            railExistsUpLeft = 13;
        if (karte[x_Pos-1][y_Pos-1].getType() == 14):
            railExistsUpLeft = 14;

        #UntenRechts

        if (karte[x_Pos+1][y_Pos+1].getType() == 9):
            railExistsDownRight = 9;
        if (karte[x_Pos+1][y_Pos+1].getType() == 10):
            railExistsDownRight = 10;
        if (karte[x_Pos+1][y_Pos+1].getType() == 11):
            railExistsDownRight = 11;
        if (karte[x_Pos+1][y_Pos+1].getType() == 12):
            railExistsDownRight = 12;
        if (karte[x_Pos+1][y_Pos+1].getType() == 13):
            railExistsDownRight = 13;
        if (karte[x_Pos+1][y_Pos+1].getType() == 14):
            railExistsDownRight = 14;

        #UntenLinks

        if (karte[x_Pos-1][y_Pos+1].getType() == 9):
            railExistsDownLeft = 9;
        if (karte[x_Pos-1][y_Pos+1].getType() == 10):
            railExistsDownLeft = 10;
        if (karte[x_Pos-1][y_Pos+1].getType() == 11):
            railExistsDownLeft = 11;
        if (karte[x_Pos-1][y_Pos+1].getType() == 12):
            railExistsDownLeft = 12;
        if (karte[x_Pos-1][y_Pos+1].getType() == 13):
            railExistsDownLeft = 13;
        if (karte[x_Pos-1][y_Pos+1].getType() == 14):
            railExistsDownLeft = 14;            
                
        return railExistsUp, railExistsDown, railExistsRight, railExistsLeft, railExistsUpRight, railExistsUpLeft, railExistsDownRight, railExistsDownLeft




        
        

