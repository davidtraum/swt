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
    @staticmethod
    def wayStationAToB(karte, pXA=0, pYA=0, pXB = 0, pYB = 0):
        originXA = pXA
        originYA = pYA
        wayTmp = []
        wayTmp.append(karte[pXA][pYA])
        
        case = 0

        while(True):

            if(case == 0):
                print("Case 0")
                #rechts
                if(not(karte[pXA+1][pYA] in wayTmp)and karte[pXA][pYA].logic.connectedRight == True):
                    print('Rechts')
                    wayTmp.append(karte[pXA+1][pYA])
                    pXA += 1    #einen nach rechts gehen
                    if(pXA == pXB and pYA == pYB):
                        return wayTmp
                #links
                elif(not(karte[pXA-1][pYA] in wayTmp) and karte[pXA][pYA].logic.connectedLeft == True):
                    print('links')
                    wayTmp.append(karte[pXA-1][pYA])
                    pXA -= 1    #einen nach links gehen
                    if(pXA == pXB and pYA == pYB):
                        return wayTmp
                #unten
                elif(not(karte[pXA][pYA+1] in wayTmp) and karte[pXA][pYA].logic.connectedDown == True):
                    print('unten')
                    wayTmp.append(karte[pXA][pYA+1])
                    pYA += 1    #einen nach unten gehen
                    if(pXA == pXB and pYA == pYB):
                        return wayTmp

                #oben
                elif(not(karte[pXA][pYA-1] in wayTmp) and karte[pXA][pYA].logic.connectedUp == True):
                    print('oben')
                    wayTmp.append(karte[pXA][pYA-1])
                    pYA -= 1    #einen nach unten gehen
                    if(pXA == pXB and pYA == pYB):
                        return wayTmp
                else:
                    case = 1    #Wenn eine Richtung Sackgasse, dann prüfe andere Richtung
                    wayTmp = []                    
                    pXA = originXA
                    pYA = originYA
                    wayTmp.append(karte[pXA][pYA])
                
            elif(case == 1):
                print("Case 1")
                #links
                if(not(karte[pXA-1][pYA] in wayTmp) and karte[pXA][pYA].logic.connectedLeft == True):
                    print('links')
                    wayTmp.append(karte[pXA-1][pYA])
                    pXA -= 1    #einen nach links gehen
                    if(pXA == pXB and pYA == pYB):
                        return wayTmp
                #rechts
                elif(not(karte[pXA+1][pYA] in wayTmp)and karte[pXA][pYA].logic.connectedRight == True):
                    print('Rechts')
                    wayTmp.append(karte[pXA+1][pYA])
                    pXA += 1    #einen nach rechts gehen
                    if(pXA == pXB and pYA == pYB):
                        return wayTmp
                #oben
                elif(not(karte[pXA][pYA-1] in wayTmp) and karte[pXA][pYA].logic.connectedUp == True):
                    print('oben')
                    wayTmp.append(karte[pXA][pYA-1])
                    pYA -= 1    #einen nach unten gehen
                    if(pXA == pXB and pYA == pYB):
                        return wayTmp
                #unten
                elif(not(karte[pXA][pYA+1] in wayTmp) and karte[pXA][pYA].logic.connectedDown == True):
                    print('unten')
                    wayTmp.append(karte[pXA][pYA+1])
                    pYA += 1    #einen nach unten gehen
                    if(pXA == pXB and pYA == pYB):
                        return wayTmp
                else:
                    case = 2    #Wenn eine Richtung Sackgasse, dann prüfe andere Richtung
                    wayTmp = []
                    pXA = originXA
                    pYA = originYA
                    wayTmp.append(karte[pXA][pYA])
                    
            elif(case == 2):
                print("Case 2")
                #oben
                if(not(karte[pXA][pYA-1] in wayTmp) and karte[pXA][pYA].logic.connectedUp == True):
                    print('oben')
                    wayTmp.append(karte[pXA][pYA-1])
                    pYA -= 1    #einen nach unten gehen
                    if(pXA == pXB and pYA == pYB):
                        return wayTmp
                 #links
                elif(not(karte[pXA-1][pYA] in wayTmp) and karte[pXA][pYA].logic.connectedLeft == True):
                    print('links')
                    wayTmp.append(karte[pXA-1][pYA])
                    pXA -= 1    #einen nach links gehen
                    if(pXA == pXB and pYA == pYB):
                        return wayTmp
                #unten
                elif(not(karte[pXA][pYA+1] in wayTmp) and karte[pXA][pYA].logic.connectedDown == True):
                    print('unten')
                    wayTmp.append(karte[pXA][pYA+1])
                    pYA += 1    #einen nach unten gehen
                    if(pXA == pXB and pYA == pYB):
                        return wayTmp
                #rechts
                elif(not(karte[pXA+1][pYA] in wayTmp)and karte[pXA][pYA].logic.connectedRight == True):
                    print('Rechts')
                    wayTmp.append(karte[pXA+1][pYA])
                    pXA += 1    #einen nach rechts gehen
                    if(pXA == pXB and pYA == pYB):
                        return wayTmp
                else:
                    case = 4    #Wenn eine Richtung Sackgasse, dann prüfe andere Richtung
                    wayTmp = []
                    pXA = originXA
                    pYA = originYA
                    wayTmp.append(karte[pXA][pYA])
                    
            elif(case == 3):
                print("Case 3")
                #unten
                if(not(karte[pXA][pYA+1] in wayTmp) and karte[pXA][pYA].logic.connectedDown == True):
                    print('unten')
                    wayTmp.append(karte[pXA][pYA+1])
                    pYA += 1    #einen nach unten gehen
                    if(pXA == pXB and pYA == pYB):
                        return wayTmp
                #rechts
                elif(not(karte[pXA+1][pYA] in wayTmp)and karte[pXA][pYA].logic.connectedRight == True):
                    print('Rechts')
                    wayTmp.append(karte[pXA+1][pYA])
                    pXA += 1    #einen nach rechts gehen
                    if(pXA == pXB and pYA == pYB):
                        return wayTmp
                #oben
                elif(not(karte[pXA][pYA-1] in wayTmp) and karte[pXA][pYA].logic.connectedUp == True):
                    print('oben')
                    wayTmp.append(karte[pXA][pYA-1])
                    pYA -= 1    #einen nach unten gehen
                    if(pXA == pXB and pYA == pYB):
                        return wayTmp
                 #links
                elif(not(karte[pXA-1][pYA] in wayTmp) and karte[pXA][pYA].logic.connectedLeft == True):
                    print('links')
                    wayTmp.append(karte[pXA-1][pYA])
                    pXA -= 1    #einen nach links gehen
                    if(pXA == pXB and pYA == pYB):
                        return wayTmp
            
                
    @staticmethod
    def  getCurves(karte, pXA, pYA, pXB, pYB, pBool = False): 
        print('vorStationAtoB')
        wayTmp = WayLogic.wayStationAToB(karte, int(pXA), int(pYA), int(pXB), int(pYB))
        print(wayTmp)
        returnTmp = ''
        for i in range(len(wayTmp)):
            print(wayTmp[i].getType())
            if(wayTmp[i].getType() != 9 and wayTmp[i].getType() != 10 and not (wayTmp[i].getType() >= 16 and wayTmp[i].getType() <= 23)):
                returnTmp += str(wayTmp[i].getX()) + ":" + str(wayTmp[i].getY()) + ";"
        if (not pBool):
            returnTmp += str(pXB) + ":" + str(pYB) + ";"
        return returnTmp[:-1]
                    
    
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
