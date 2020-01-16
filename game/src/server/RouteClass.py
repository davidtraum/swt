from WayClass import *
from PlayerClass import *
from TrainClass import TrainLogic
import time


class RouteLogic:
    allRoutes = []
    def __init__(self, pPlayer, pTrainstations, pWagons, pTrainName = 'testtrain'):
        self.player = pPlayer
        self.trainstations = pTrainstations
        self.wagons = pWagons
        self.train = TrainLogic(pTrainName)  #neuer Zug
        self.timeNeeded = []        #Anzahl der Schienen
        self.last_mach_was = 0
        self.stationCounter = 0 #Zähler an welchen Bahnhof man ist
        self.calculateTime()
        self.train.addWagons(self.trainstations[0], self.trainstations[1], self.wagons) #erste Strecke

    def calculateTime(self):
        for i in range(len(self.trainstations)-1):
            print(self.trainstations[i])
            print(self.trainstations[i+1])
            self.timeNeeded.append(WayLogic.getLength(self.trainstations[i], self.trainstations[i+1]))
        
            
            
        
    def do_loop(self):                       
        if(time.time() - self.last_mach_was > float(self.timeNeeded[self.stationCounter]) * 0.5):
            print("Bahnhof ",self.stationCounter," erreicht")
            self.train.removeWagon(self.wagons)            
            print(len(self.trainstations))
            if(self.stationCounter == len(self.trainstations)-1):
                self.train.addWagons(self.trainstations[self.stationCounter], self.trainstations[self.stationCounter-1], self.wagons) 
                self.stationCounter = 0
            else:
                self.train.addWagons(self.trainstations[self.stationCounter], self.trainstations[self.stationCounter+1], self.wagons)           
                self.stationCounter += 1
            self.last_mach_was = time.time()
            
    