from WayClass import *
from TrainClass import TrainLogic
import time


class RouteLogic:
    allRoutes = []
    countId = 0
    def __init__(self, pPlayer, pTrainstations, pWagons, pKarte, pTrainName = 'testtrain'):
        self.player = pPlayer
        self.karte = pKarte
        self.trainstations = pTrainstations
        self.wagons = pWagons
        self.train = TrainLogic(pTrainName)  #neuer Zug
        RouteLogic.countId += 1
        self.id = RouteLogic.countId
        self.timeNeeded = []        #Anzahl der Schienen
        self.last_mach_was = 0
        self.stationCounter = 0 #Zähler an welchen Bahnhof man ist
        #self.calculateTime()
        #self.train.addWagons(self.trainstations[0], self.trainstations[1], self.wagons) #erste Strecke

    def sendProtocolString(self):
        tmpCurves = ''
        for i in range(len(self.trainstations)-1):
            x1 = self.trainstations[i].getX()
            y1 = self.trainstations[i].getY()
            x2 = self.trainstations[i+1].getX()
            y2 = self.trainstations[i+1].getY()  
            tmpCurves += WayLogic.getCurves(self.karte, x1, y1, x2, y2)
            tmpCurves += ';'
        print(tmpCurves)
        x1 = self.trainstations[0].getX()
        y1 = self.trainstations[0].getY()
        x2 = self.trainstations[-1].getX()
        y2 = self.trainstations[-1].getY()

        print("DAS MUSS REIN ------------  " +  WayLogic.getCurves(self.karte, x2, y2, x1, y1, True))
        
        if (WayLogic.getCurves(self.karte, x2, y2, x1, y1, True) == ""):
            tmpCurves = tmpCurves[:-1]
        
        return str(self.countId) + "+" + str(x1) + ":" + str(y1) + ";" + tmpCurves + WayLogic.getCurves(self.karte, x2, y2, x1, y1, True)

    
    def calculateTime(self):    #Berechnet die benötigte Zeit, die die Route in Anspruch nimmt
        for i in range(len(self.trainstations)-1):
            print(self.trainstations[i])
            print(self.trainstations[i+1])            
            self.timeNeeded.append(WayLogic.getLength(self.trainstations[i], self.trainstations[i+1]))           
            tmp = WayLogic.wayStationAToB(self.karte, self.trainstations[-1].getX(), self.trainstations[-1].getY(), self.trainstations[0].getX(), self.trainstations[0].getY())
            
        self.timeNeeded.append(len(tmp))
        print (self.timeNeeded)

        
            
            
        
    def do_loop(self):  #Der Loop, der die Züge in der Logik die Route abfahren lässt                      
        if(time.time() - self.last_mach_was > float(self.timeNeeded[self.stationCounter]) * 0.5):
            print("Bahnhof ",self.stationCounter," erreicht")
            self.train.removeWagon(self.wagons)            
            print(len(self.trainstations))
            if(self.stationCounter == len(self.trainstations)-1):
                self.train.addWagons(self.trainstations[self.stationCounter], self.trainstations[-1], self.wagons) 
                self.stationCounter = 0
            else:
                self.train.addWagons(self.trainstations[self.stationCounter], self.trainstations[self.stationCounter+1], self.wagons)           
                self.stationCounter += 1
            self.last_mach_was = time.time()
            
    
