#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "player.h"
#include "Score.h"
#include "Health.h"
#include <QElapsedTimer>
#include "RoadLines.h"
#include <vector>

class Game: public QGraphicsView{
public:
    Game(QWidget * parent=0);

    QGraphicsScene * scene;
    Player * player;
    Score * score;
    Health * health;
    int scoreInterval = 500; // current interval of the score timer

public slots:
    void increaseScore();
};

#endif // GAME_H
