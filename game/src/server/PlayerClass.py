import json
from RailClass import RailLogic
from TrainStationClass import TrainStationLogic

class Player:

    def __init__(self, pId, pIp):
        self.id = pId;
        self.ip = pIp;
        #Beim Laden von Speicherdaten muss das Spielerobjekt mit gespeichertem Guthaben neu erstellt werden
        with open('playerData.json', 'r') as f:
            playerData =json.load(f);
            if (self.id == 1):
                money = playerData['p1_money'];    #Guthaben wird aus playerData-JSON ausgelesen
            if (self.id == 2):
                money = playerData['p2_money'];    #Guthaben wird aus playerData-JSON ausgelesen
            if (self.id == 3):
                money = playerData['p3_money'];    #Guthaben wird aus playerData-JSON ausgelesen
            if (self.id == 4):
                money = playerData['p4_money'];    #Guthaben wird aus playerData-JSON ausgelesen

    def getMoney(self):
        return self.money;

    def getIp(self):
        return self.ip;
    
    def isOwnerRail(self, railObject):  #Prüft Gültigkeit einer Aktion des Spielers (Besitz des Objekts), z.B. beim Abreißen von Schienen benötigt
        if (self.id == railObject.player):  #Spieler-ID passt zur im Objekt gespeicherten ID?
            return True;
        else:
            return False;

    def isOwnerTrainstration(self, trainStationObject):  #Prüft Gültigkeit einer Aktion des Spielers (Besitz des Objekts)
        if (self.id == trainStationObject.player):   #Spieler-ID passt zur im Objekt gespeicherten ID?
            return True;
        else:
            return False;

    def addValue(self, amount): #fügt Guthaben zum Konto des Spielers hinzu (negativer Wert: Abzug)
        self.money += amount;


    def __del__(self):  #Werte wie Guthaben müssen in JSON gespeichert werden, wenn der Spieler offline geht.
        with open('playerData.json', 'r+') as f:
            playerData = json.load(f);
            data['money'] = self.money; #Guthaben wird gesichert
            f.seek(0);
            json.dump(playerData, f, indent = 4)
            f.truncate();
            
            
