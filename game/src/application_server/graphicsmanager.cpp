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
    GRAPHICS.insert(std::pair<std::string, QPixmap>("schiene_kurve", QPixmap::fromImage(QImage(":/images/schienen/schiene_kurve.png"))));

    GRAPHICS.insert(std::pair<std::string, QPixmap>("water", QPixmap::fromImage(QImage(":/images/water.png"))));
}

/**
 * @brief GraphicsManager::get Liefert eine Grafik mit einem bestimmten Namen.
 * @param key Name der Grafik.
 * @return  Die Grafik.
 */
QPixmap GraphicsManager::get(std::string key){
    return GRAPHICS[key];
}


