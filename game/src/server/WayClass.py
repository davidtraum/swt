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
        for i in range(None, (len(WayLogic.allWays))):
            print(i)
            if(WayLogic.allWays[i].firstTrainStation != None):
                s += 'WAY ' + str(i+1) + ' FIRSTSTATION ' + 'POSX ' + str(WayLogic.allWays[i].firstTrainStation.getX()) + ' POSY ' + str(WayLogic.allWays[i].firstTrainStation.getY())
            for j in range(None, len(WayLogic.allWays[i].firstRail)):
                s+= ' POSX ' +str(WayLogic.allWays[i].firstRail[j].getX()) + ' POSY ' + str(WayLogic.allWays[i].firstRail[j].getY())
            if(WayLogic.allWays[i].secondTrainStation != None):
                s += ' SECONDSTATION ' + 'POSX ' + str(WayLogic.allWays[i].secondTrainStation.getX()) + ' POSY ' + str(WayLogic.allWays[i].secondTrainStation.getY())
            s+= 'Laenge :' + str(len(WayLogic.allWays[i].firstRail))
            s+='\n'
        
        return s


    @staticmethod
    def getTrainstationProtocolString(pos_X, pos_Y, karte):
        s = ''  
        print(karte[pos_X][pos_Y].getType())
        if(karte[pos_X][pos_Y].getType() == 16 or karte[pos_X][pos_Y].getType() == 18 or karte[pos_X][pos_Y].getType() == 20):     
            print('ist horizontal')
            if(karte[pos_X+1][pos_Y].logic != None):
                print('rechts')
                if(karte[pos_X+1][pos_Y].logic.way.firstTrainStation != karte[pos_X][pos_Y]):
                    if(karte[pos_X+1][pos_Y].logic.way.firstTrainStation != None):                        
                        print('firstTraistation')
                        s+= 'reachable Trainstation Pos_X: ' +str(karte[pos_X+1][pos_Y].logic.way.firstTrainStation.getX()) + ' Pos_Y: ' +str(karte[pos_X+1][pos_Y].logic.way.firstTrainStation.getY()) + "\n"
                else:
                    if(karte[pos_X+1][pos_Y].logic.way.secondTrainStation != None):
                        print('secondTraistation')
                        s+= 'reachable Trainstation Pos_X: ' +str(karte[pos_X+1][pos_Y].logic.way.secondTrainStation.getX()) + ' Pos_Y: ' +str(karte[pos_X+1][pos_Y].logic.way.secondTrainStation.getY()) + "\n"
            if(karte[pos_X-1][pos_Y].logic != None):
                print('links')
                if(karte[pos_X-1][pos_Y].logic.way.firstTrainStation != karte[pos_X][pos_Y]):
                    if(karte[pos_X-1][pos_Y].logic.way.firstTrainStation != None):
                        print('firstTraistation')
                        s+= 'reachable Trainstation Pos_X: ' +str(karte[pos_X-1][pos_Y].logic.way.firstTrainStation.getX()) + ' Pos_Y: ' +str(karte[pos_X-1][pos_Y].logic.way.firstTrainStation.getY()) + "\n"
                else:
                    if(karte[pos_X-1][pos_Y].logic.way.secondTrainStation != None):
                        s+= 'reachable Trainstation Pos_X: ' +str(karte[pos_X-1][pos_Y].logic.way.secondTrainStation.getX()) + ' Pos_Y: ' +str(karte[pos_X-1][pos_Y].logic.way.secondTrainStation.getY()) + "\n"
                        print('secondTnstation')
        else:
            print('ist vertikal')
            if(karte[pos_X][pos_Y-1].logic != None):
                print('unten')
                if(karte[pos_X][pos_Y-1].logic.way.firstTrainStation != karte[pos_X][pos_Y-1]):
                    if(karte[pos_X][pos_Y-1].logic.way.firstTrainStation != None):
                        print('firstTraistation')
                        s+= 'reachable Trainstation Pos_X: ' +str(karte[pos_X][pos_Y-1].logic.way.firstTrainStation.getX()) + ' pos_Y: ' +str(karte[pos_X][pos_Y-1].logic.way.firstTrainStation.getY()) + "\n"
                else:
                    if(karte[pos_X][pos_Y-1].logic.way.secondTrainStation != None):
                        print('secondTnstation')
                        s+= 'reachable Trainstation Pos_X: ' +str(karte[pos_X][pos_Y-1].logic.way.secondTrainStation.getX()) + ' pos_Y: ' +str(karte[pos_X][pos_Y-1].logic.way.secondTrainStation.getY()) + "\n"
            if(karte[pos_X][pos_Y+1].logic != None):
                print('oben')
                if(karte[pos_X][pos_Y+1].logic.way.firstTrainStation != karte[pos_X][pos_Y+1]):
                    if(karte[pos_X][pos_Y+1].logic.way.firstTrainStation != None):
                        print('firstTraistation')
                        s+= 'reachable Trainstation Pos_X: ' +str(karte[pos_X][pos_Y+1].logic.way.firstTrainStation.getX()) + ' pos_Y: ' +str(karte[pos_X][pos_Y+1].logic.way.firstTrainStation.getY()) + "\n"
                else:
                    if(karte[pos_X+1][pos_Y].logic.way.secondTrainStation != None):
                        print('secondTnstation')
                        s+= 'reachable Trainstation Pos_X: ' +str(karte[pos_X][pos_Y+1].logic.way.secondTrainStation.getX()) + ' pos_Y: ' +str(karte[pos_X][pos_Y+1].logic.way.secondTrainStation.getY()) + "\n"          
                      
        return s