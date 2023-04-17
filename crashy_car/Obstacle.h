#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsRectItem>
#include <QObject>

class Obstacle: public QObject,public QGraphicsRectItem{
    Q_OBJECT
public:
    Obstacle();
public slots:
    void move();
};


#endif // OBSTACLE_H
