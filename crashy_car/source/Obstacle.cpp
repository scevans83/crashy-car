#include "Obstacle.h"
#include "Game.h"
#include "player.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include <random>

extern Game * game;

Obstacle::Obstacle(Player* player, QGraphicsItem* parent)
    : QObject(), QGraphicsPixmapItem(parent), player(player){
  // Each time objects are created they are set an a random position along the road
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(45,192);
    int random_number = dis(gen);
    setPos(510,random_number);
    QPixmap obst (":/graphics/pothole2.png");
    obst = obst.scaled(30,30);
    QRectF obstacleRect = this->boundingRect();
    // make the rectangle smaller for collision detection
    obstacleRect.adjust(10, 10, -10, -10);
    setPixmap (QPixmap (obst));

    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(5);
}

void Obstacle::move(){
    if (!game->gameOver) {

        setPos(x()-3,y());

        // check for collision with the smaller rectangle
        if (collidesWithItem(player, Qt::IntersectsItemBoundingRect) && player->collidesWithItem(this, Qt::IntersectsItemBoundingRect))
        {
            // collision detected
            printf("COLLISION!\n");
            game->loser();
        }

    }//game over

    if(pos().x() + 30 < 0 || game->gameOver) {
        scene()->removeItem(this);
        delete this;
    }

}
