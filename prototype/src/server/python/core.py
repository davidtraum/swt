from threading import Thread
import random

class ClientThread(Thread):
    
    def __init__(self, connection, address):
        Thread.__init__(self);
        self.connection = connection;
        self.address = address;
        self.start();
        
    def send(self, msg):
        self.connection.sendall(msg.encode("utf-8"));
        
    def run(self):
        global WORLD;
        print("[THREAD] Client verbunden " + str(self.address));
        self.send("CONN ACTIVE");
        while True:
            command = self.connection.recv(32);
            split = command.split(" ");
            if(split[0]=='MAP'):
                if(split[1]=='GET'):
                    self.send(WORLD.serialize());
        
class MapTile:
    
    def __init__(self):
        self.rotation = 0;
        self.tileType = 'GRASS';
    
    def setType(self, pType):
        self.tileType = pType;
    
    def setRotation(self, pRotation):
        self.rotation = pRotation;
        
        
class World:
    
    def __init__(self):
        self.data = [];
        self.generate();
        
    def serialize(self):
        global CONFIG;
        data = "";
        for x in range(CONFIG['world']['size']):
            for y in range(CONFIG['world']['size']):
                data+=self.data[x][y].tileType + ',' + str(self.data[x][y].rotation) + ';';
        return data;
        
    def generate(self):
        global CONFIG;
        print(CONFIG);
        self.data = [];
        print("[WELT] Welt wird generiert...");
        for x in range(CONFIG['world']['size']):
            self.data.append([]);
            for y in range(CONFIG['world']['size']):
                tile = MapTile();
                if(random.random()>0.8):
                    tile.setType('FORREST');
                else:
                    tile.setType('GRASS');
                tile.setRotation(random.randint(0,3));
        
            
