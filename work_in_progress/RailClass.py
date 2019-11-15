from GameLogicObject import GameLogicObject

class RailLogic(GameLogicObject):

    @staticmethod
    def _checkRails(self, x_Pos, y_Pos, karte):
        railExistsUp = 0; #4-dim Array für 4 Seiten eines Quadranten
        railExistsDown = 0;
        railExistsLeft = 0;
        railExistsRight = 0;

        if (karte[x_Pos+1][y_Pos] == "rail"):
            #hier check inhalt
            railExistsRight = 1;

        if (karte[x_Pos][y_Pos+1] == "rail"):
            #hier check inhalt
            railExistsDown = 1;

        if (karte[x_Pos-1][y_Pos] == "rail"):
            #hier check inhalt
            railExistsLeft = 1;

        if (karte[x_Pos][y_Pos-1] == "rail"):
            #hier check inhalt
            railExistsUp = 1;

        return railExistsUp, railExistsDown, railExistsRight, railExistsLeft;

        
