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
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(45,192);
    int random_number = dis(gen);
    setPos(510,random_number);
    QPixmap obst (":/graphics/pothole2.png");
    obst = obst.scaled(30,30);
    QRectF obstacleRect = this->boundingRect();
    // make the rectangle smaller
    obstacleRect.adjust(10, 10, -10, -10);
    setPixmap (QPixmap (obst));

    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(5);
}

void Obstacle::move(){
    if (!game->gameOver) {

    QElapsedTimer timer;
    timer.start();

    // check for collision with the smaller rectangle
    if (collidesWithItem(player, Qt::IntersectsItemBoundingRect) && player->collidesWithItem(this, Qt::IntersectsItemBoundingRect))
    {
        // collision detected
        printf("COLLISION!\n");
        game->loser();
    }

    setPos(x()-3,y());

    // Calculate the time elapsed since the last frame
    qint64 elapsed = timer.elapsed();

    // Adjust the movement based on the elapsed time
    qreal offset = -3.0 * elapsed / 200.0;
    setPos(x(), y() + offset);
    }

    //game over
    if(pos().x() + 30 < 0 || game->gameOver) {
        auto it = std::find(Player::obst_vect.begin(), Player::obst_vect.end(), this); // find this object in the vector
        if (it != Player::obst_vect.end()) {
            Player::obst_vect.erase(it); // remove this object from the vector
//            printf("Erased an object from vector\n");
        }
        scene()->removeItem(this);
        delete this;
    }

}
