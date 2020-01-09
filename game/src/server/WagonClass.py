from TrainStationClass import TrainStationLogic

class WagonLogic:
    def __init__(self, pStartTrainstation, pEndTrainstation, pType):
        self.capcity = 50
        self.type = pType
        self.amount = 0
        self.startTrainstation = pStartTrainstation
        self.endTrainstation = pEndTrainstation

    def loadWagon(self, pamount):
        maxGood = self.startTrainstation.STORAGE[self.type]
        if pamount >= maxGood:
            self.amount = maxGood
        else:
            self.amount = pamount
        
        if self.amount + pamount <= self.capcity:
            self.amount += pamount
            return True
        else:
            print("Kapazität wurde überschritten!")
            return False
   
    def unloadWagon(self, pAmount):
        trainstationGood = self.endTrainstation.STORAGE[self.type]
        if self.amount - pAmount >= 0:
            self.amount -= pAmount
            trainstationGood += self.amount
            return True
        elif self.amount + trainstationGood > self.endTrainstation.maxStorage:
            print("Entladungsmenge ist zu hoch!")
            return False     
    

