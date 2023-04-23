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
    //set random position
    //    geterate:
    //    int random_number = arc4random() % 700;
    //    if(random_number < 150 || random_number + 30 > 650)
    //        goto geterate;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0,19);
    int random_number = dis(gen);
    setPos(510,random_number);
    QPixmap tree (":/graphics/palm_tree1.png");
    //obst = obst.scaled(30,30);
    setPixmap (QPixmap (tree));
    collisionEllipse = new QGraphicsEllipseItem(this);
    QRectF collisionRect = this->boundingRect();
    collisionRect.adjust(15, 15, -15, -15); // modify the rect to create a smaller ellipse
    collisionEllipse->setRect(collisionRect);
    collisionEllipse->setPen(Qt::NoPen);
    collisionEllipse->setBrush(Qt::transparent);
    collisionEllipse->setPos(this->pos());


    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(5);
}

void LeftSide::move(){
    //    printf("Obstacles in vector: %zull\n", Player::obst_vect.size());
    QElapsedTimer timer;
    timer.start();

    // check for collision with the smaller rectangle
    if (player->collidesWithItem(collisionEllipse, Qt::IntersectsItemBoundingRect))
    {
        // collision detected
        printf("TREE COLLISION!\n");
    }
    setPos(x()-3,y());

    // Calculate the time elapsed since the last frame
    qint64 elapsed = timer.elapsed();

    // Adjust the movement based on the elapsed time
    qreal offset = -3.0 * elapsed / 200.0;
    setPos(x(), y() + offset);

    collisionEllipse->setPos(this->pos());

    if(pos().x() + 30 < 0) {
//        auto it = std::find(Player::obst_vect.begin(), Player::obst_vect.end(), this); // find this object in the vector
//        if (it != Player::obst_vect.end()) {
//            Player::obst_vect.erase(it); // remove this object from the vector
//            //            printf("Erased an object from vector\n");
//        }
        scene()->removeItem(this);
        delete this;
    }
}
