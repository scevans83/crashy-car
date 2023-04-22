#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "QtWidgets/qpushbutton.h"
#include "player.h"
#include "Score.h"
#include "Health.h"
#include "RoadLines.h"
#include <QElapsedTimer>
#include <vector>

class Game: public QGraphicsView{
public:
    Game(QWidget * parent=0);

    QGraphicsScene * scene;
    Player * player;
    Score * score;
    Health * health;
    int scoreInterval = 500; // current interval of the score timer
    bool gameOver;
    bool gameActive;


public slots:
    void increaseScore();
    void loser();
    void startGame();
    void restartGame();
private:
    QPushButton* replayButton;
};

#endif // GAME_H
