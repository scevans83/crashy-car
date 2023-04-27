#ifndef STARTBTN_H
#define STARTBTN_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class StartBtn : public QGraphicsPixmapItem
{
public:
    StartBtn(QGraphicsItem *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    QGraphicsTextItem *text;

signals:
    void clicked();
};

#endif // STARTBTN_H
