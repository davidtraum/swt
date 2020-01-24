
from WagonClass import WagonLogic

class TrainLogic:
    def  __init__(self, name = "testzug"):
        self.trainName = name
        self.speed = 10
        self.maxWagons = 10
        self.wagons = []

    def addWagons(self, pStartTrainstation, pType):   #Waggons werden angehängt
        for i in range(len(pType)):        
            self.wagons.append(WagonLogic(pStartTrainstation, None, pType[i]))
            self.wagons[i].loadWagon()
        return True
        
    def removeWagon(self, pEndTrainstation, pType):   #Waggons werden abgekoppelt
        self.wagons.endTrainstation = pEndTrainstation
        for i in range(len(pType)):
            self.wagons[-1].unloadWagon()
            self.wagons.pop()
        return True
