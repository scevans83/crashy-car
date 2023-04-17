#include "player.h"
#include <QDebug>
#include <QKeyEvent>
#include "Obstacle.h"
#include <QGraphicsScene>
#include "RoadLines.h"

void Player::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Left) {
        if(pos().x() > 150){
            setPos (x () -15,y());
        }
    }
    else if (event->key () == Qt::Key_Right) {
        if(pos().x() + 100 < 650){
            setPos (x () +15,y ());
        }
    }
}

void Player::spawn()
{
    Obstacle * obstacle = new Obstacle;
    scene()->addItem(obstacle);
}

void Player::lines(){
    RoadLines * newline = new RoadLines;
    scene()->addItem(newline);

}
