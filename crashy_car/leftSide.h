
#ifndef LEFTSIDE_H
#define LEFTSIDE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QElapsedTimer>

class Player;

class LeftSide: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    LeftSide(Player* player, QGraphicsItem* parent = nullptr);
    qreal yPos() const { return y(); }
    void setYPos(qreal y) { setY(y); }
public slots:
    void move();
private:
    qreal speed;
    Player* player;
    QGraphicsEllipseItem* collisionEllipse;
};

#endif // LEFTSIDE_H
