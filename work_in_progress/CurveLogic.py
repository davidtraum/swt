from RailClass import RailLogic



CurveDirection = {
    "upRight" : 1
    "upLeft" : 2
    "downRight" : 3
    "downLeft" : 4
    "rightUp" : 5
    "rightDown" : 6
    "leftUp" : 7
    "leftDown" : 8
    "unknown" : 9};
    

class CurveLogic:

    def __init__(self, px_Pos, py_Pos):
        self.x_Pos = px_Pos;
        self.y_Pos = py_Pos;        
        self.direction = "unknown"
        
        

test = CurveLogic()
print(test.direction)
    
