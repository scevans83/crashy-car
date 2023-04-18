#include "Obstacle.h"
#include "Game.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include <random>

extern Game * game;

Obstacle::Obstacle(): QObject(), QGraphicsPixmapItem(){
    //set random position
//    geterate:
//    int random_number = arc4random() % 700;
//    if(random_number < 150 || random_number + 30 > 650)
//        goto geterate;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(45,192);
    int random_number = dis(gen);
    setPos(510,random_number);
    QPixmap obst (":/graphics/pothole.png");
    obst = obst.scaled(30,30);
    setPixmap (QPixmap (obst));
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(15);
}

void Obstacle::move(){
    QElapsedTimer timer;
    timer.start();

    setPos(x()-9,y());

    // Calculate the time elapsed since the last frame
    qint64 elapsed = timer.elapsed();

    // Adjust the movement based on the elapsed time
    qreal offset = -9.0 * elapsed / 200.0;
    setPos(x(), y() + offset);

    if(pos().y() + 30 < 0) {
        scene()->removeItem(this);
        delete this;
    }
}
