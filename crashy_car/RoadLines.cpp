#include "RoadLines.h"
#include "Game.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include <QElapsedTimer>

extern Game * game;

RoadLines::RoadLines(): QObject(), QGraphicsRectItem(0, 0, 10, 70){
    setPos(395, -70);
    setZValue(-1);
    QBrush brush(QColor(254, 195, 94));
        setBrush(brush);
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(50);
}

void RoadLines::move(){

    setPos(x(),y()+5);

    if(pos().y() - 30 > 600) {
        scene()->removeItem(this);
        delete this;
    }
}

