#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QElapsedTimer>

class Obstacle: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Obstacle();
public slots:
    void move();
private:
    qreal speed;
};


#endif // OBSTACLE_H
