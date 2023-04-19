#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>

class Player: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    void keyPressEvent(QKeyEvent * event);
public slots:
    void spawn();
    void lines();
    void updatePlayerPosition(int xAccel);
private:
    int threshold = 400;

};

#endif // PLAYER_H
