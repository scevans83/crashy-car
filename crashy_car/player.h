#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include "Obstacle.h"
#include "leftSide.h"
#include "rightside.h"

class Player: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Player(QGraphicsItem* parent = nullptr);
    static std::vector<Obstacle *> obst_vect;
    //static std::vector<LeftSide *> ls_vect;
    void keyPressEvent(QKeyEvent * event);
    QGraphicsEllipseItem* collisionEllipse;
public slots:
    void spawn();
    void spawn_ls();
    void spawn_rs();
    void lines();
    void updatePlayerPosition(int xAccel);
    void updateTimers();
private:
    int threshold = 400;
};

#endif // PLAYER_H
