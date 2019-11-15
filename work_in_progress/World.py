from RailClass import RailLogic

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

    def railPlaced(self, px, py):
        self.railExistsUp, self.railExistsDown, self.railExistsRight, self.railExistsLeft = RailLogic._checkRails(self, px, py, self.map);

karte = World();
karte.railPlaced(4,7);
print(karte.railExistsUp);
print(karte.railExistsDown);
print(karte.railExistsRight);
print(karte.railExistsLeft);

