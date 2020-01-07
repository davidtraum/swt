from RouteClass import RouteLogic
from WagonClass import WagonLogic

class TrainLogic:
    def  __init__(self, name = "testzug"):
        self.trainName = name
        self.speed = 10
        self.maxWagons = 10
        self.wagons = []

    def addWagons(self, pWagon):
        if len(self.wagons) <= self.maxWagons: 

            self.wagons.append(pWagon)
            return True
        else:
            print("Zu viele wagons!")
            return False
        
    def removeWagon(self, digit):
        if digit < len(self.wagons):
            self.wagons.pop(digit)
            return True
        else:
            print("Keine Elemente ")
            return False


    


    

