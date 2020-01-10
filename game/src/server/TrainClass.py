from RouteClass import RouteLogic
from WagonClass import WagonLogic

class TrainLogic:
    def  __init__(self, name = "testzug"):
        self.trainName = name
        self.speed = 10
        self.maxWagons = 10
        self.wagons = []

    def addWagons(self, pWagon, pStartTrainstation, pEndTrainstation, pType):
        for i in range(len(pType)):        
            self.wagons.append(pWagon(pStartTrainstation, pEndTrainstation, pType[i]))
            self.wagons[i].loadWagon()
        return True
        
    def removeWagon(self, pType):
        for i in range(len(pType)):
            self.wagons[-1].unloadWagon()
            self.wagons.pop()
        return True