import json
from RailClass import RailLogic
from TrainStationClass import TrainStationLogic
from WayClass import WayLogic
from RouteClass import RouteLogic
import uuid as uuidmodule

def uuid():
    return uuidmodule.uuid4().hex

class Player:

    def __init__(self, pIp, pTasks, pKarte, pMoney):
        self.id = uuid()
        self.ip = pIp
        self.tasks = pTasks
        self.karte = pKarte
        self.routes = []
        self.routeObjectList = []
        #Beim Laden von Speicherdaten muss das Spielerobjekt mit gespeichertem Guthaben neu erstellt werden
        """with open('playerData.json', 'r') as f:
            playerData =json.load(f)
            if (self.id == 1):
                self.money = playerData['p1_money']    #Guthaben wird aus playerData-JSON ausgelesen
            if (self.id == 2):
                self.money = playerData['p2_money']    #Guthaben wird aus playerData-JSON ausgelesen
            if (self.id == 3):
                self.money = playerData['p3_money']    #Guthaben wird aus playerData-JSON ausgelesen
            if (self.id == 4):
                self.money = playerData['p4_money']    #Guthaben wird aus playerData-JSON ausgelesen
        """

        self.money = pMoney

    #Gibt das Guthaben des Spielers zurück
    def getMoney(self):
        return self.money

    def hasMoney(self, count):
        return self.money >= count

    #Gibt die IP des Spielers zurück
    def getIp(self):
        return self.ip

    #Gibt True zurück, wenn der Spieler Besitzer der Schiene ist
    def isOwnerRail(self, railObject):  #Prüft Gültigkeit einer Aktion des Spielers (Besitz des Objekts), z.B. beim Abreißen von Schienen benötigt
        if (self.id == railObject.player):  #Spieler-ID passt zur im Objekt gespeicherten ID?
            return True
        else:
            return False
        
    #Gibt True zurück, wenn der Spieler Besitzer des Bahnhofs ist
    def isOwnerTrainstration(self, trainStationObject):  #Prüft Gültigkeit einer Aktion des Spielers (Besitz des Objekts)
        if (self.id == trainStationObject.player):   #Spieler-ID passt zur im Objekt gespeicherten ID?
            return True
        else:
            return False

    #Fügt dem Konto des Spielers Guthaben hinzu (negativ -> Geld wird abgezogen)
    def addValue(self, amount): #fügt Guthaben zum Konto des Spielers hinzu (negativer Wert: Abzug)
        self.money += amount

    #Füge eine Route zur Liste aller Routen des Spielers hinzu 
    def addRoute(self, pRouteName, pRoute, pWagons):      
        self.routes.append([pRouteName, pRoute, pWagons])
        print("Route hinzugefügt. Aktuelle Routen des Spielers: ")
        print(self.routes)
        print("Neue Route wird gestartet.")
        return self.startRoute(self.routes[-1][0], self.routes[-1][1], self.routes[-1][2])

    #Startet die übergebene Route
    def startRoute(self, pRouteName, pStations, pWagons):     
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
        for i in range(len(self.routeObjectList)):      #Hier bei mehreren Routen in der Liste manchmal "list index out of range"?
            print("In For Schleife gesprungen")
            if (self.routeObjectList[i].routeName == pRouteName):
                tmpID = self.routeObjectList[i].id
                print("ID wird gelöscht: " + str(tmpID))
                del self.routeObjectList[i]
                return tmpID
        print("ROUTE GELÖSCHT: " + pRouteName)
                
    #Werte wie Guthaben sollten in JSON gespeichert werden, wenn der Spieler offline geht.
    def __del__(self):  
        #with open('playerData.json', 'r+') as f:
        #    playerData = json.load(f)
        #    data['money'] = self.money #Guthaben wird gesichert
        #    f.seek(0)
        #    json.dump(playerData, f, indent = 4)
        #    f.truncate()
        pass

    
            
   
