#include "leftSide.h"
#include "Game.h"
#include "player.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include <random>

extern Game * game;

LeftSide::LeftSide(Player* player, QGraphicsItem* parent)
    : QObject(), QGraphicsPixmapItem(parent), player(player){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0,19);
    int random_number = dis(gen);
    setPos(510,random_number);
    QPixmap tree (":/graphics/cactus.png");
    setPixmap (QPixmap (tree));
    QRectF collisionRect = this->boundingRect();
    collisionRect.adjust(10, 10, -10, -10); // modify the rect to create a smaller rectangle

    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(5);
}

void LeftSide::move(){
    if (!game->gameOver) {
    // Update the position of the LeftSide object
    setPos(x()-3,y());

    // check for collision
    if (player->collidesWithItem(this, Qt::IntersectsItemBoundingRect))
    {
        // collision detected
        printf("CACTUS COLLISION!\n");
        game->loser();
    }
    }

    //game over
    if(pos().x() + 30 < 0 || game->gameOver) {
        scene()->removeItem(this);
        delete this;
    }
}
