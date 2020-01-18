#include <QDebug>

#include "graphicsmanager.h"


/**
 * @brief GraphicsManager::GraphicsManager Lädt alle Grafiken. Neue bitte im selben Stil ergänzen.
 */
GraphicsManager::GraphicsManager(){
    GRAPHICS.insert(std::pair<std::string, QPixmap>("grass", QPixmap::fromImage(QImage(":/images/grass.png"))));
    GRAPHICS.insert(std::pair<std::string, QPixmap>("wald", QPixmap::fromImage(QImage(":/images/wald.png"))));
    GRAPHICS.insert(std::pair<std::string, QPixmap>("stadt", QPixmap::fromImage(QImage(":/images/stadt.png"))));
    GRAPHICS.insert(std::pair<std::string, QPixmap>("rathaus", QPixmap::fromImage(QImage(":/images/rathaus.png"))));

    GRAPHICS.insert(std::pair<std::string, QPixmap>("fluss_h", QPixmap::fromImage(QImage(":/images/fluss/fluss_horizontal.png"))));
    GRAPHICS.insert(std::pair<std::string, QPixmap>("fluss_v", QPixmap::fromImage(QImage(":/images/fluss/fluss_vertikal.png"))));
    GRAPHICS.insert(std::pair<std::string, QPixmap>("fluss_rb", QPixmap::fromImage(QImage(":/images/fluss/fluss_kurve_rechts_unten.png"))));
    GRAPHICS.insert(std::pair<std::string, QPixmap>("fluss_rt", QPixmap::fromImage(QImage(":/images/fluss/fluss_kurve_rechts_oben.png"))));
    GRAPHICS.insert(std::pair<std::string, QPixmap>("fluss_lt", QPixmap::fromImage(QImage(":/images/fluss/fluss_kurve_links_oben.png"))));
    GRAPHICS.insert(std::pair<std::string, QPixmap>("fluss_lb", QPixmap::fromImage(QImage(":/images/fluss/fluss_kurve_links_unten.png"))));

    GRAPHICS.insert(std::pair<std::string, QPixmap>("schiene_h", QPixmap::fromImage(QImage(":/images/schienen/schiene_h.png"))));
    GRAPHICS.insert(std::pair<std::string, QPixmap>("schiene_v", QPixmap::fromImage(QImage(":/images/schienen/schiene_v.png"))));
    GRAPHICS.insert(std::pair<std::string, QPixmap>("schiene_kurve", QPixmap::fromImage(QImage(":/images/schienen/schiene_kurve.png"))));
    GRAPHICS.insert(std::pair<std::string, QPixmap>("water", QPixmap::fromImage(QImage(":/images/water.png"))));

    GRAPHICS.insert(std::pair<std::string, QPixmap>("bahnhof", QPixmap::fromImage(QImage(":/images/trainstation.png"))));
    GRAPHICS.insert(std::pair<std::string, QPixmap>("depot", QPixmap::fromImage(QImage(":/images/depot.png"))));
    GRAPHICS.insert(std::pair<std::string, QPixmap>("terminal", QPixmap::fromImage(QImage(":/images/terminal.png"))));

    GRAPHICS.insert(std::pair<std::string, QPixmap>("bruecke", QPixmap::fromImage(QImage(":/images/bruecke.png"))));

    GRAPHICS.insert(std::pair<std::string, QPixmap>("zug", QPixmap::fromImage(QImage(":/images/train_top.png"))));

    //Produktionsgebäude:
    GRAPHICS.insert(std::pair<std::string, QPixmap>("kohlemine", QPixmap::fromImage(QImage(":/images/coalmine.png"))));
    GRAPHICS.insert(std::pair<std::string, QPixmap>("gueter", QPixmap::fromImage(QImage(":/images/factorygoods.png"))));
    GRAPHICS.insert(std::pair<std::string, QPixmap>("getreide", QPixmap::fromImage(QImage(":/images/grain.png"))));
    GRAPHICS.insert(std::pair<std::string, QPixmap>("essen", QPixmap::fromImage(QImage(":/images/foodproc.png"))));
    GRAPHICS.insert(std::pair<std::string, QPixmap>("petrolium", QPixmap::fromImage(QImage(":/images/oilwell.png"))));
    GRAPHICS.insert(std::pair<std::string, QPixmap>("papier", QPixmap::fromImage(QImage(":/images/papermill.png"))));
    GRAPHICS.insert(std::pair<std::string, QPixmap>("vieh", QPixmap::fromImage(QImage(":/images/ranchlivestock.png"))));
    GRAPHICS.insert(std::pair<std::string, QPixmap>("holz", QPixmap::fromImage(QImage(":/images/wood.png"))));
    GRAPHICS.insert(std::pair<std::string, QPixmap>("stahl", QPixmap::fromImage(QImage(":/images/steel_factory.png"))));
}

/**
 * @brief GraphicsManager::get Liefert eine Grafik mit einem bestimmten Namen.
 * @param key Name der Grafik.
 * @return  Die Grafik.
 */
QPixmap GraphicsManager::get(std::string key){
    return GRAPHICS[key];
}


