
#ifndef FINALSCORE_H
#define FINALSCORE_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include "Score.h"

class FinalScore : public QGraphicsRectItem
{
public:
    FinalScore(QGraphicsItem *parent = nullptr);
    int score = 0;
    int high_score = 0;
    QGraphicsTextItem *score_text;
    QGraphicsTextItem *hs_text;
    QGraphicsTextItem *new_hs_text;

signals:
    void clicked();
};

#endif // FINALSCORE_H
