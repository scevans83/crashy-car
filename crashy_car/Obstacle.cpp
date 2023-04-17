#include "Obstacle.h"
#include "Game.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>

extern Game * game;

Obstacle::Obstacle(): QObject(), QGraphicsPixmapItem(){
    //set random position
    geterate:
    int random_number = arc4random() % 700;
    if(random_number < 150 || random_number + 30 > 650)
        goto geterate;
    setPos(random_number,-30);
    setPixmap (QPixmap (":/graphics/pothole.png"));
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(50);
}

void Obstacle::move(){

    setPos(x(),y()+5);

    if(pos().y() - 30 > 600) {
        scene()->removeItem(this);
        delete this;
    }
}
