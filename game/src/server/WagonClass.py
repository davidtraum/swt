from TrainStationClass import TrainStationLogic

class WagonLogic:   #Waggons werden an Züge angehängt
    def __init__(self, pStartTrainstation, pEndTrainstation, pType, pPlayer):
        self.capacity = 50
        self.type = pType
        self.amount = 0
        self.startTrainstation = pStartTrainstation
        self.endTrainstation = pEndTrainstation
        self.player = pPlayer

    def loadWagon(self):    #Belädt Waggon mit Gütern
        print('vor beladen:', self.startTrainstation.logic.STORAGE[self.type])
        if(self.startTrainstation.logic.PRICES[self.type] < self.endTrainstation.logic.PRICES[self.type]):
            maxGood = self.startTrainstation.logic.STORAGE[self.type]
            if self.capacity <= maxGood :
                self.amount += self.capacity #füllt Wagon komplett
                self.player.money -= self.capacity * self.startTrainstation.logic.PRICES[self.type]            
                self.startTrainstation.logic.STORAGE[self.type] -= self.capacity #entfernt Menge aus Lager
                print('nach beladen:', self.startTrainstation.logic.STORAGE[self.type])
                return True
            else:
                self.amount += maxGood
                self.player.money -= maxGood * self.startTrainstation.logic.PRICES[self.type]
                self.startTrainstation.logic.STORAGE[self.type] -= maxGood
                print('nach beladen:', self.startTrainstation.logic.STORAGE[self.type])
                return True
        else:
            print('kein Gewinn möglich')
            return False

    def unloadWagon(self):  #Entlädt Waggon
        trainstationGood = self.endTrainstation.logic.STORAGE[self.type]
        if self.amount + trainstationGood <= self.endTrainstation.logic.maxStorage:
            self.endTrainstation.logic.STORAGE[self.type] += self.amount
            self.player.money += self.amount * self.startTrainstation.logic.PRICES[self.type]
            return True
        elif self.amount + trainstationGood > self.endTrainstation.logic.STORAGE[self.type]:
            self.endTrainstation.logic.STORAGE[self.type] = self.endTrainstation.logic.maxStorage
            self.player.money += self.amount * self.startTrainstation.logic.PRICES[self.type]
            return False     
    

