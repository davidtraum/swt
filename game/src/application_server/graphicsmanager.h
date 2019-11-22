#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include <QPixmap>
#include <QImage>
#include <string>

class GraphicsManager
{
public:
    GraphicsManager();
    QPixmap get(std::string key);
    std::map<std::string, QPixmap> GRAPHICS;
};

#endif // GRAPHICSMANAGER_H
