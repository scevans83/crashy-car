
#ifndef RIGHTSIDE_H
#define RIGHTSIDE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QElapsedTimer>

class Player;

class RightSide: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    RightSide(Player* player, QGraphicsItem* parent = nullptr);
    qreal yPos() const { return y(); }
    void setYPos(qreal y) { setY(y); }
public slots:
    void move();
private:
    qreal speed;
    Player* player;
    QGraphicsEllipseItem* collisionEllipse;
};



#endif // RIGHTSIDE_H
