#include "finalscore.h"
#include <QFont>
#include <QBrush>
#include <QPen>
#include "Game.h"

extern Game * game;

FinalScore::FinalScore(QGraphicsItem *parent)
    : QGraphicsRectItem(parent)
{
    // Set the size and color of the button
    QFont font("Arial", 14);
    setRect(200, 36, 150, 200);
    setBrush(QBrush(Qt::black));
    setPen(QPen(Qt::NoPen));
    score_text = new QGraphicsTextItem(this);
    score_text->setDefaultTextColor(Qt::white);
    score_text->setRotation(90);
    score_text->setFont(font);
    score_text->setPos(350, 46);
    setVisible(false);
    score_text->setVisible(false);

    hs_text = new QGraphicsTextItem(this);
    hs_text->setRotation(90);
    hs_text->setFont(font);
    hs_text->setPos(290, 46);
    hs_text->setDefaultTextColor(Qt::white);

    new_hs_text = new QGraphicsTextItem(this);
    new_hs_text->setRotation(90);
    new_hs_text->setFont(font);
    new_hs_text->setPos(290, 46);
    new_hs_text->setPlainText(QString("It's a new High Score!!"));
    new_hs_text->setDefaultTextColor(Qt::white);

    setVisible(false);
    score_text->setVisible(false);
    //text->setTextWidth(rect().height());
}
