class WayLogic:    
    allWays = []
    
    def __init__(self, pPlayer):
        self.player = pPlayer # Spieler X
        self.firstTrainStation = None
        self.secondTrainStation = None
        self.firstRail = []
        self.secondRail = []
        self.waySections = []

    @staticmethod
    def getProtocolString():
        s = ''
        for i in range(0, (len(WayLogic.allWays))):
            print(i)
            if(WayLogic.allWays[i].firstTrainStation != None):
                s += 'WAY ' + str(i+1) + ' FIRSTSTATION ' + 'POSX ' + str(WayLogic.allWays[i].firstTrainStation.getX()) + ' POSY ' + str(WayLogic.allWays[i].firstTrainStation.getY())
            for j in range(0, len(WayLogic.allWays[i].firstRail)):
                s+= ' POSX ' +str(WayLogic.allWays[i].firstRail[j].getX()) + ' POSY ' + str(WayLogic.allWays[i].firstRail[j].getY())
            if(WayLogic.allWays[i].secondTrainStation != None):
                s += ' SECONDSTATION ' + 'POSX ' + str(WayLogic.allWays[i].secondTrainStation.getX()) + ' POSY ' + str(WayLogic.allWays[i].secondTrainStation.getY())
            s+='\n'
            s+= str(len(WayLogic.allWays[i].firstRail))
        return s