#include "player.h"
#include <QDebug>
#include <QKeyEvent>
#include "Game.h"
#include "Obstacle.h"
#include <QGraphicsScene>
#include "RoadLines.h"

extern Game * game;

Player::Player(QGraphicsItem* parent)
    : QObject(), QGraphicsPixmapItem(parent){

    QPixmap car_orig(":/graphics/car.png");
    QPixmap car_img = car_orig.scaled(QSize(25,50));
    setPixmap(car_img);
    setPos(60, 136);
    setRotation(90);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    }

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
    if(game->gameActive && !game->gameOver){
    if (xAccel > 200) {
        // Move player to the right
        if(pos().y() + 31 < 272){
            setPos(x(), y() + 15);
        }
    } else if (xAccel < -400) {
        // Move player to the left
        if(pos().y() - 10 > 0){
            setPos(x(), y() - 15);
        }
    }
    }
}

// Create new pothole object
void Player::spawn()
{
    if (game->gameActive && !game->gameOver){
    Obstacle * obstacle = new Obstacle(this);
    scene()->addItem(obstacle);
    }
}

//Create left side cactcus
void Player::spawn_ls()
{
    if (game->gameActive && !game->gameOver){
    LeftSide *ls = new LeftSide(this);
    scene()->addItem(ls);
    }
}

//Create right side cactus
void Player::spawn_rs()
{
    if (game->gameActive && !game->gameOver){
    RightSide *rs = new RightSide(this);
    scene()->addItem(rs);
    }
}

// Create roadlines
void Player::lines(){
    if (game->gameActive && !game->gameOver){
    RoadLines * newline = new RoadLines;
    scene()->addItem(newline);
    }
}

/* Reduce the timer interval for object creation by 10% and increase 
   the Update timer by 10%. This makes the game get 10% harder after the Update
   timer expires but then the timer is 10% longer, so the rate of increased 
   difficulty decreases as the game goes on.*/ 
void Player::updateTimers()
{
    if (game->gameActive && !game->gameOver){
    printf("Difficulty Increased!\n");
    game ->obst_timer1_val = game ->obst_timer1_val * 0.9;
    game ->ls_cactus_val = game ->ls_cactus_val * 0.9;
    game ->rs_cactus_val = game ->rs_cactus_val * 0.9;
    game->ls_cactus->setInterval(game->ls_cactus_val);
    game->rs_cactus->setInterval(game->rs_cactus_val);
    game->obst_timer1->setInterval(game->obst_timer1_val);
    game->incr_diff_timer_val = game->incr_diff_timer_val *1.10;
    game->incr_diff_timer->setInterval(game->incr_diff_timer_val);
    }
}

