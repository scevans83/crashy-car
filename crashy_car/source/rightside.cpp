#include "rightside.h"
#include "Game.h"
#include "player.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include <random>

extern Game * game;

/* Create a cactus obstacle on the right side in specified range and set
   a timer to update the movement every 5ms*/
RightSide::RightSide(Player* player, QGraphicsItem* parent)
    : QObject(), QGraphicsPixmapItem(parent), player(player){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(220,244);
    int random_number = dis(gen);
    setPos(510,random_number);
    QPixmap tree (":/graphics/cactus.png");
    setPixmap (QPixmap (tree));
    QRectF collisionRect = this->boundingRect();
    collisionRect.adjust(10, 10, -10, -10); // modify the bounding rect used for collision detection

    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(5);
}

void RightSide::move(){
    if (!game->gameOver) {
        // Update the position of the RightSide object
        setPos(x()-3,y());

        // check for collision
        if (player->collidesWithItem(this, Qt::IntersectsItemBoundingRect))
        {
            // collision detected
            printf("CACTUS COLLISION!\n");
            game->loser();
        }
    }//gameover

    if(pos().x() + 30 < 0 || game->gameOver) {
        scene()->removeItem(this);
        delete this;
    }
}
