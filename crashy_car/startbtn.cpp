#include "startbtn.h"
#include <QFont>
#include <QBrush>
#include <QPen>
#include "Game.h"

extern Game * game;

StartBtn::StartBtn (QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
{
    // Set the size and color of the button
    QPixmap startButton(":/graphics/startButton.png"); //120x46
    setPixmap(startButton);
    setPos(85,76);
    setRotation(90);
//    setRect(50, 86, 50, 100);
//    setBrush(QBrush(Qt::darkGreen));
//    setPen(QPen(Qt::NoPen));
//    text = new QGraphicsTextItem(this);
//    text->setPlainText(QString("Start"));
//    text->setDefaultTextColor(Qt::white);
//    text->setRotation(90);
//    QFont font("Arial", 20);
//    text->setFont(font);
//    text->setPos(96, 102);
    //text->setTextWidth(rect().height());
}

void StartBtn::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //QGraphicsRectItem::mousePressEvent(event);
    game->startGame();
    //text->setVisible(false);
    setVisible(false);
    printf("Pressed!\n");
}
