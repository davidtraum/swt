from GoodClass import GoodLogic

class WagonLogic:
    def __init__(self, pGood):
        self.capcity = 3000
        self.goodName = pGood.name
        self.amount = 0

    def loadWagon(self, amount):
        if self.amount + amount <= self.capcity:
            self.amount += amount
            return True
        else:
            print("Kapazität wurde überschritten!")
            return False
   
    def unloadWagon(self, amount):
        if self.amount - amount >= 0:
            self.amount -= amount
            return True
        else:
            print("Entladungsmenge ist zu hoch!")
            return False     
    

