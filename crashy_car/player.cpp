#include "player.h"
#include <QDebug>
#include <QKeyEvent>
#include "Game.h"
#include "Obstacle.h"
#include <QGraphicsScene>
#include "RoadLines.h"

extern Game * game;
std::vector<Obstacle *> Player::obst_vect;

void Player::keyPressEvent(QKeyEvent *event){
    if (game->gameActive && !game->gameOver){
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
}

void Player::updatePlayerPosition(int xAccel) {
    // Change the player's position based on the accelerometer data
    //printf("X acceleration: %d \n",xAccel);
    if(game->gameActive && !game->gameOver){
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
}

void Player::spawn()
{
    if (game->gameActive && !game->gameOver){
    Obstacle * obstacle = new Obstacle(this);
    obst_vect.push_back(obstacle);
    //printf("obstacle count:%d \n", obst_vect.size());
    scene()->addItem(obstacle);
    }
}

void Player::lines(){
    if (game->gameActive && !game->gameOver){
    RoadLines * newline = new RoadLines;
    scene()->addItem(newline);
    }
}
