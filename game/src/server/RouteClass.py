from WayClass import *
from PlayerClass import *

class RouteLogic:
    def __init__(self, pPlayer):
        self.player = pPlayer
        self.ways = [] 

    def addWay(self, pWay):
        self.ways.append(pWay)