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
#include <QLabel>

class Game: public QGraphicsView{
public:
    Game(QWidget * parent=0);

    QGraphicsScene * scene;
    Player * player;
    Score * score;
    Health * health;
    int scoreInterval = 500; // current interval of the score timer
    QTimer* obst_timer1;
    QTimer* obst_timer2;
    QTimer* ls_tree;
    QTimer* rs_tree;
    bool gameOver;
    bool gameActive;
    bool newHighScore;
    bool firstScore;


public slots:
    void increaseScore();
    void loser();
    void startGame();
    void restartGame();
private:
    QPushButton* replayButton;
    QLabel* scoreLabel;
    QLabel* highScoreLabel;
    QLabel* newHighScoreLabel;

};

#endif // GAME_H
