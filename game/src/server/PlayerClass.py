import json
from RailClass import RailLogic
from TrainStationClass import TrainStationLogic
from WayClass import WayLogic
from RouteClass import RouteLogic

class Player:

    def __init__(self, pId, pIp, pTasks, pKarte):
        self.id = pId
        self.ip = pIp
        self.tasks = pTasks
        self.karte = pKarte
        self.routes = []
        self.routeObjectList = []
        #Beim Laden von Speicherdaten muss das Spielerobjekt mit gespeichertem Guthaben neu erstellt werden
        with open('playerData.json', 'r') as f:
            playerData =json.load(f)
            if (self.id == 1):
                self.money = playerData['p1_money']    #Guthaben wird aus playerData-JSON ausgelesen
            if (self.id == 2):
                self.money = playerData['p2_money']    #Guthaben wird aus playerData-JSON ausgelesen
            if (self.id == 3):
                self.money = playerData['p3_money']    #Guthaben wird aus playerData-JSON ausgelesen
            if (self.id == 4):
                self.money = playerData['p4_money']    #Guthaben wird aus playerData-JSON ausgelesen

    def getMoney(self):
        return self.money

    def getIp(self):
        return self.ip
    
    def isOwnerRail(self, railObject):  #Prüft Gültigkeit einer Aktion des Spielers (Besitz des Objekts), z.B. beim Abreißen von Schienen benötigt
        if (self.id == railObject.player):  #Spieler-ID passt zur im Objekt gespeicherten ID?
            return True
        else:
            return False

    def isOwnerTrainstration(self, trainStationObject):  #Prüft Gültigkeit einer Aktion des Spielers (Besitz des Objekts)
        if (self.id == trainStationObject.player):   #Spieler-ID passt zur im Objekt gespeicherten ID?
            return True
        else:
            return False

    def addValue(self, amount): #fügt Guthaben zum Konto des Spielers hinzu (negativer Wert: Abzug)
        self.money += amount

    def addRoute(self, pRouteName, pRoute, pWagons):    #Füge eine Route zur Liste aller Routen des Spielers hinzu   
        self.routes.append([pRouteName, pRoute, pWagons])
        print("Route hinzugefügt. Aktuelle Routen des Spielers: ")
        print(self.routes)
        print("Neue Route wird gestartet.")
        return self.startRoute(self.routes[-1][0], self.routes[-1][1], self.routes[-1][2])

    def startRoute(self, pRouteName, pStations, pWagons):     #Startet die übergebene Route
        tsTmp = []
        for i in range(len(pStations)):
            tsTmp.append(self.karte[int(pStations[i][0])][int(pStations[i][1])])    
        self.routeObjectList.append(RouteLogic(None, tsTmp, pWagons, self.karte, pRouteName))
        handOver = self.routeObjectList[-1].sendProtocolString()        
        return handOver

    #Löscht die Route (Objekt und Listenelement) mit dem passenden Namen
    def cancelRoute(self, pRouteName):
        for i in range(len(self.routes)):
            if (self.routes[i][0] == pRouteName):
                self.routes.pop(i)
                print("route popped")
        for i in range(len(self.routeObjectList)):
            if (self.routeObjectList[i].routeName == pRouteName):
                tmpID = self.routeObjectList[i].id
                print("ID wird gelöscht: " + str(tmpID))
                del self.routeObjectList[i]
                return tmpID
        print("ROUTE GELÖSCHT: " + pRouteName)
                
        
    def __del__(self):  #Werte wie Guthaben müssen in JSON gespeichert werden, wenn der Spieler offline geht.
        #with open('playerData.json', 'r+') as f:
        #    playerData = json.load(f)
        #    data['money'] = self.money #Guthaben wird gesichert
        #    f.seek(0)
        #    json.dump(playerData, f, indent = 4)
        #    f.truncate()
        pass

    
            
   
