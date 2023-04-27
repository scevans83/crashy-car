#include "finalscore.h"
#include <QFont>
#include <QBrush>
#include <QPen>
#include "Game.h"

extern Game * game;

//Displays the final score at the end of the game
FinalScore::FinalScore(QGraphicsItem *parent)
    : QGraphicsRectItem(parent)
{
  // Score text
    QFont font("Arial", 20);
    setRect(200, 11, 100, 250);
    setBrush(QBrush(Qt::black));
    setPen(QPen(Qt::NoPen));
    score_text = new QGraphicsTextItem(this);
    score_text->setDefaultTextColor(Qt::white);
    score_text->setRotation(90);
    score_text->setFont(font);
    score_text->setPos(245, 80);
    setVisible(false);
    score_text->setVisible(false);
    
    // Text for current high score
    hs_text = new QGraphicsTextItem(this);
    hs_text->setRotation(90);
    hs_text->setFont(font);
    hs_text->setPos(300, 45);
    hs_text->setDefaultTextColor(Qt::white);

    // Text for a new high score
    font.setPointSize(14);
    new_hs_text = new QGraphicsTextItem(this);
    new_hs_text->setRotation(90);
    new_hs_text->setFont(font);
    new_hs_text->setPos(300, 31);
    new_hs_text->setPlainText(QString("  You totally crashed it!\nThat's a new high score!"));
    new_hs_text->setDefaultTextColor(Qt::white);

    setVisible(false);
    score_text->setVisible(false);
}
