from abc import ABC, abstractmethod

class GameLogicObject(ABC):
    #abstract
    def __init__(self, px_Pos, py_Pos):
        self.x_Pos = px_Pos;
        self.y_Pos = py_Pos;
    
    
