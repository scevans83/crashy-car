#include "player.h"
#include <QDebug>
#include <QKeyEvent>
#include "Obstacle.h"
#include <QGraphicsScene>
#include "RoadLines.h"

void Player::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Left) {
        if(pos().y() - 10 > 0){
            setPos (x(),y() -15);
        }
    }
    else if (event->key () == Qt::Key_Right) {
        if(pos().y() + 31 < 272){
            setPos (x() ,y()+15);
        }
    }
}

void Player::updatePlayerPosition(int xAccel) {
    // Change the player's position based on the accelerometer data
    printf("X acceleration: %d ",xAccel); // Add this line to check the value of xAccel
    if (xAccel > threshold) {
        // Move player to the right
        if(pos().y() + 31 < 272){
            setPos(x(), y() + 15);
        }
    } else if (xAccel < -threshold) {
        // Move player to the left
        if(pos().y() - 10 > 0){
            setPos(x(), y() - 15);
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
