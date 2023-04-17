#include "MyRect.h"
#include <QDebug>
#include <QKeyEvent>
#include "Obstacle.h"
#include <QGraphicsScene>

void MyRect::keyPressEvent(QKeyEvent *event){
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

void MyRect::spawn()
{
    Obstacle * obstacle = new Obstacle;
    scene()->addItem(obstacle);
}
