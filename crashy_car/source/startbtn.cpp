#include "startbtn.h"
#include <QFont>
#include <QBrush>
#include <QPen>
#include "Game.h"

extern Game * game;


StartBtn::StartBtn (QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
{
    // Set the size and color of the button image
    QPixmap startButton(":/graphics/startButton.png"); //120x46
    setPixmap(startButton);
    setPos(85,76);
    setRotation(90);
}

// Event handler for when button is "clicked" on touchscreen
void StartBtn::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    game->startGame();
    setVisible(false);
}
