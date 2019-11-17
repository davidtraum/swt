from RailClass import *

class Grass:
    def __init__(self, px_Pos, py_Pos):
        self.x_Pos = px_Pos;
        self.y_Pos = py_Pos;

class World:

    def __init__(self):
        #Kartengenerierung
        self.map = [[Grass(i,j) for i in range(30)] for j in range(30)];
        print("Karte mit Gras generiert");

    def changeMaptile(self, px, py, newMaptile):
        self.map[px][py] = newMaptile;

    def checkRailSurroundings(self, px, py):
        self.railExistsUp, self.railExistsDown, self.railExistsRight, self.railExistsLeft = RailLogic._checkRails(self, px, py, self.map);

    def setRail(self, px, py, rail):
        self.railPlaced(px, py); 
        if (railExistsUp + railExistsDown + railExistsRight + railExistsLeft == 1):
            #wenn nur eine andere Schiene braucht es maximal eine Kurve/max. 1 Maptile muss verändert werden
            if (railExistsRight == 1 and self.direction == 0):  #upRight
                curve = CurveLogic
                CurveLogic.curvedirection = CurveDirection.UpRight
                self.map[px-1][py] = curve


karte = World();
karte.map[4][8] = RailLogic;
karte.checkRailSurroundings(4,7);
print(karte.railExistsUp);
print(karte.railExistsDown);
print(karte.railExistsRight);
print(karte.railExistsLeft);

