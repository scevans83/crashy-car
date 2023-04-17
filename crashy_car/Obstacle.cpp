#include "Obstacle.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>

Obstacle::Obstacle(): QObject(), QGraphicsRectItem(){
    //set random position
    int random_number = rand() % 600;
    setPos(random_number,0);
    setRect(0,0,50,50);
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(50);
}

void Obstacle::move(){
    setPos(x(),y()+5);
    if(pos().y() - rect().height() > 600) {
        scene()->removeItem(this);
        delete this;
    }
}
