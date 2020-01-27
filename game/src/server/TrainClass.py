
from WagonClass import WagonLogic

class TrainLogic:
    def  __init__(self, pPlayer, name = "testzug"):
        self.trainName = name
        self.speed = 10
        self.maxWagons = 10
        self.wagons = []
        self.player = pPlayer
        self.wagonList = []

    def addWagons(self, pStartTrainstation, pEndTrainstation, pType, pPlayer):   #Waggons werden angehängt
        self.wagonList = pType
        for i in range(len(pType)):        
            self.wagons.append(WagonLogic(pStartTrainstation, pEndTrainstation, pType[i], pPlayer))
            self.wagons[i].loadWagon()
        return True
        
    def removeWagons(self, pEndTrainstation):   #Waggons werden abgekoppelt        
        for i in range(len(self.wagonList)):            
            self.wagons[-1].unloadWagon()
            self.wagons.pop()
        return True
