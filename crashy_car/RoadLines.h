// RoadLines.h

#ifndef ROADLINES_H
#define ROADLINES_H

#include <QGraphicsRectItem>
#include <QTimer>

class RoadLines : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    RoadLines();
public slots:
    void move();
private:
    qreal speed;
    qreal lineSpacing;
};

#endif // ROADLINES_H
