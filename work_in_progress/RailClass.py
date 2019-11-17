from GameLogicObject import GameLogicObject
from enum import Enum

class RailLogic(GameLogicObject):

    def __init__(self, px_Pos, py_Pos):
        self.x_Pos = px_Pos;
        self.y_Pos = py_Pos;        
        self.Direction = 0; #0 ist horizontal #1 ist vertikal

    @staticmethod
    def _checkRails(self, x_Pos, y_Pos, karte):
        railExistsUp = 0; 
        railExistsDown = 0;
        railExistsLeft = 0;
        railExistsRight = 0;

        if (karte[x_Pos+1][y_Pos] == RailLogic):
            #hier check inhalt
            railExistsRight = 1;

        if (karte[x_Pos][y_Pos+1] == RailLogic):
            #hier check inhalt
            railExistsDown = 1;

        if (karte[x_Pos-1][y_Pos] == RailLogic):
            #hier check inhalt
            railExistsLeft = 1;

        if (karte[x_Pos][y_Pos-1] == RailLogic):
            #hier check inhalt
            railExistsUp = 1;                
                

        return railExistsUp, railExistsDown, railExistsRight, railExistsLeft;

        


class CurveDirection(Enum):
    topRight = 1
    topLeft = 2
    downRight = 3
    downLeft = 4
    rightUp = 5
    rightDown = 6
    leftUp = 7
    leftDown = 8
    unknown = 9

    

class CurveLogic(RailLogic):

    def __init__(self, px_Pos, py_Pos):
        self.x_Pos = px_Pos;
        self.y_Pos = py_Pos;        
        self.curveDirection = CurveDirection.unknown

        
        

