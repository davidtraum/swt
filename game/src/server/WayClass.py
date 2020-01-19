class WayLogic:    
    allWays = []
    
    def __init__(self, pPlayer):
        self.player = pPlayer # Spieler X
        self.firstTrainStation = None
        self.secondTrainStation = None
        self.firstRail = []
        self.secondRail = []
        self.waySections = []



    #gibt Länge von Bahnhof A nach B    
    def wayStationAToB(karte, pXA=0, pYA=0, pXB = 0, pYB = 0):
        wayTmp = []
        wayTmp.append(karte[pXA][pYA])
        while(True):
            #rechts
            if(not(karte[pXA+1][pYA] in wayTmp) and (karte[pXA+1][pYA].isRail() or karte[pXA+1][pYA].isTrainStation())):
                wayTmp.append(karte[pXA+1][pYA])
                pXA += 1    #einen nach rechts gehen
                if(pXA == pXB and pYA == pYB):
                    return wayTmp
            #links
            if(not(karte[pXA-1][pYA] in wayTmp) and (karte[pXA-1][pYA].isRail() or karte[pXA-1][pYA].isTrainStation())):
                wayTmp.append(karte[pXA-1][pYA])
                pXA -= 1    #einen nach links gehen
                if(pXA == pXB and pYA == pYB):
                    return wayTmp
            #unten
            if(not(karte[pXA][pYA+1] in wayTmp) and (karte[pXA][pYA+1].isRail() or karte[pXA][pYA+1].isTrainStation())):
                wayTmp.append(karte[pXA][pYA+1])
                pYA += 1    #einen nach unten gehen
                if(pXA == pXB and pYA == pYB):
                    return wayTmp

            #oben
            if(not(karte[pXA][pYA-1] in wayTmp) and (karte[pXA][pYA-1].isRail() or karte[pXA][pYA-1].isTrainStation())):
                wayTmp.append(karte[pXA][pYA-1])
                pYA -= 1    #einen nach unten gehen
                if(pXA == pXB and pYA == pYB):
                    return wayTmp
            
            
                
                
                    
    
    @staticmethod
    def getLength(pTrainStationA, pTrainStationB):  #Gibt die Länge der Strecke zurück
        print(pTrainStationA)
        print(pTrainStationB)
        for i in range(0, len(WayLogic.allWays)):
            if(WayLogic.allWays[i].firstTrainStation==pTrainStationA or WayLogic.allWays[i].secondTrainStation == pTrainStationA):
                if(WayLogic.allWays[i].firstTrainStation ==pTrainStationB or WayLogic.allWays[i].secondTrainStation == pTrainStationB):
                    s = len(WayLogic.allWays[i].firstRail)
                    print("benötigte Zeit/Länge:", s)
                    return s

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
