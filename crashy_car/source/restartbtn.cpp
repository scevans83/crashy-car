#include "restartbtn.h"
#include <QFont>
#include <QBrush>
#include <QPen>
#include "Game.h"

extern Game * game;

RestartBtn::RestartBtn(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
{
    // Set the size and position of button image
    QPixmap restartButton(":/graphics/restartButton.png"); //120x46
    setPixmap(restartButton);
    setPos(160,76);
    setRotation(90);
    setVisible(false);
}

// Event handler for when button is "clicked" on touchscreen
void RestartBtn::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    game->restartGame();
    setVisible(false);
}
