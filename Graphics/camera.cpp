#include "camera.h"
#include <QSize>
#include "GameObjects/Actors/player.h"

Camera::Camera(int meters, QWidget * parent)
{
    metersPerScreen = meters;
    QSize size = parent->frameSize();
    screenWidth = size.width();
    screenHeight = size.height();
    pixPerMeter = screenWidth / meters;
}

Camera::~Camera(){
}

std::vector<GameObject*> * Camera::snapshot(Player * center, KDTree<GameObject*> * tree){
    tree->remove(center);
    QPoint* cent = center->getCenter();
    std::vector<GameObject*> actors = tree->rangeSearch(center, cent->x() - metersPerScreen / 2, cent->y() + metersPerScreen / 2,
                                                        cent->x() + metersPerScreen / 2, center->y() - metersPerScreen / 2);
    double leftX = center->getCenter()->x() - (metersPerScreen / 2);
    double topY = center->getCenter()->y() + ((screenHeight / pixPerMeter) / 2);
    std::vector<GameObject *> * toDraw = new std::vector<GameObject*>();
    for(std::vector<GameObject *>::iterator it = actors.begin(); it != actors.end(); ++it) {
        GameObject * current = *it;
        double xDisplacement = current->x() - leftX;
        double yDisplacement = topY - current->y();
        double xPixels = xDisplacement * pixPerMeter;
        double yPixels = yDisplacement * pixPerMeter;
        current->drawingX = xPixels;
        current->drawingY = yPixels;
        double heightPixels = current->getHeight() * pixPerMeter;
        double widthPixels = current->getWidth() * pixPerMeter;
        current->drawingWidth = widthPixels;
        current->drawingHeight = heightPixels;
        toDraw->push_back(current);
    }
    center->drawingX = screenWidth / 2;
    center->drawingY = screenHeight / 2;
    center->drawingHeight = center->getRadius() * pixPerMeter;
    center->drawingWidth = center->getRadius() * pixPerMeter;
    toDraw->push_back(center);
    tree->insert(center);
    return toDraw;
}
