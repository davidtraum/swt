from TrainStationClass import TrainStationLogic

class WagonLogic:   #Waggons werden an Züge angehängt
    def __init__(self, pStartTrainstation, pEndTrainstation, pType):
        self.capacity = 50
        self.type = pType
        self.amount = 0
        self.startTrainstation = pStartTrainstation
        self.endTrainstation = pEndTrainstation

    def loadWagon(self):    #Belädt Waggon mit Gütern
        print('vor beladen:', self.startTrainstation.logic.STORAGE[self.type])
        maxGood = self.startTrainstation.logic.STORAGE[self.type]
        if self.capacity <= maxGood :
            self.amount += self.capacity #füllt Wagon komplett
            self.startTrainstation.logic.STORAGE[self.type] -= self.capacity #entfernt Menge aus Lager
            print('nach beladen:', self.startTrainstation.logic.STORAGE[self.type])
            return True
        else:
            self.amount += maxGood
            self.startTrainstation.logic.STORAGE[self.type] -= maxGood
            print('nach beladen:', self.startTrainstation.logic.STORAGE[self.type])
            return True

    def unloadWagon(self):  #Entlädt Waggon
        trainstationGood = self.endTrainstation.logic.STORAGE[self.type]
        if self.amount + trainstationGood <= self.endTrainstation.logic.maxStorage:
            self.endTrainstation.logic.STORAGE[self.type] += self.amount
            return True
        elif self.amount + trainstationGood > self.endTrainstation.logic.STORAGE:
            self.endTrainstation.logic.STORAGE[self.type] = self.endTrainstation.logic.max.Storage
            return False     
    

