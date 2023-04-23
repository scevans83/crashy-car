#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QElapsedTimer>

class Player;

class Obstacle: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Obstacle(Player* player, QGraphicsItem* parent = nullptr);
    qreal yPos() const { return y(); }
    void setYPos(qreal y) { setY(y); }
public slots:
    void move();
signals:
    void collision();
private:
    qreal speed;
    Player* player;
};


#endif // OBSTACLE_H
