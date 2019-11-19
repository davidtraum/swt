from RailClass import *
import types
class World:

    def __init__(self):
        self.data = [[ 'GRASS' for i in range(300)] for j in range(300)]


karte = World()
print(karte.data[1][1])

karte.data[10][20] = RailLogic(10, 20, 1)
print(type(karte.data[10][20]))

RailLogic.build(11, 20, 1, karte.data) #Schiene rechts gebaut
RailLogic.build(10, 21, 1, karte.data) #Schiene oben gebaut
print(karte.data[10][20].getConnections())
print(karte.data[10][20].connectedUp)

#for i in range(0,299):
   # for j in range(0,299):
       # if(karte.data[i][j] == "Grass"):
           # print("0")
       # else:
           # print("1")
