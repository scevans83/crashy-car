#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include "Obstacle.h"

class Player: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    static std::vector<Obstacle *> obst_vect;
    void keyPressEvent(QKeyEvent * event);
public slots:
    void spawn();
    void lines();
    void updatePlayerPosition(int xAccel);
private:
    int threshold = 400;

};

#endif // PLAYER_H
