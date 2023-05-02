#include "RoadLines.h"
#include "Game.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include <QElapsedTimer>

extern Game * game;

// Create a new Roadline Object in the middle of the road and set a timer to move it every 15ms
RoadLines::RoadLines(): QObject(), QGraphicsRectItem(0, 0, 70, 5){
    setPos(485, 136);
    setZValue(-1);
    QBrush brush(QColor(254, 195, 94));
        setBrush(brush);
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(15);
}

// Moves roadlines objects down the screen until it reach a point off screen. Then it is deleted.
void RoadLines::move(){
    if(!game->gameOver) {
        QElapsedTimer timer;
        timer.start();

        setPos(x() - 9, y());
    }
    if(pos().x() + 30 < 0) {
        scene()->removeItem(this);
        delete this;
    }
}

