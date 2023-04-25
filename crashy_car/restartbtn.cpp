#include "restartbtn.h"
#include <QFont>
#include <QBrush>
#include <QPen>
#include "Game.h"

extern Game * game;

RestartBtn::RestartBtn(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
{
    // Set the size and color of the button
    QPixmap restartButton(":/graphics/restartButton.png"); //120x46
    setPixmap(restartButton);
    setPos(160,76);
    setRotation(90);
//    setRect(50, 86, 50, 100);
//    setBrush(QBrush(QColorConstants::Svg::darkorange));
//    setPen(QPen(Qt::NoPen));
//    text = new QGraphicsTextItem(this);
//    text->setPlainText(QString("Reset"));
//    text->setDefaultTextColor(Qt::white);
//    text->setRotation(90);
//    QFont font("Arial", 20);
//    text->setFont(font);
//    text->setPos(96, 102);
    setVisible(false);
//    text->setVisible(false);
    //text->setTextWidth(rect().height());
}

void RestartBtn::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //QGraphicsRectItem::mousePressEvent(event);
    game->restartGame();
    //text->setVisible(false);
    setVisible(false);
    printf("Pressed!\n");
}
