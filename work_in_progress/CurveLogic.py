from RailClass import RailLogic
from enum import Enum

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

    

class CurveLogic:

    def __init__(self, px_Pos, py_Pos):
        self.x_Pos = px_Pos;
        self.y_Pos = py_Pos;        
        self.direction = CurveDirection.unknown
        
        

test = CurveLogic()
print(test.direction)
    
