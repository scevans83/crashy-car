
#ifndef RESTARTBTN_H
#define RESTARTBTN_H
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class RestartBtn : public QGraphicsPixmapItem
{
public:
    RestartBtn(QGraphicsItem *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    QGraphicsTextItem *text;

signals:
    void clicked();
};

#endif // RESTARTBTN_H
