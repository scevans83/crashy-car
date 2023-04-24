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
#include "startbtn.h"
#include "restartbtn.h"
#include "finalscore.h"

class Game: public QGraphicsView{
public:
    Game(QWidget * parent=0);

    QGraphicsScene * scene;
    Score * score;
    Health * health;
    int scoreInterval = 500; // current interval of the score timer
    QTimer* obst_timer1;
    QTimer* obst_timer2;
    QTimer* ls_cactus;
    QTimer* rs_cactus;
    QTimer* incr_diff_timer;
    int obst_timer1_val;
    int obst_timer2_val;
    int ls_cactus_val;
    int rs_cactus_val;
    int incr_diff_timer_val = 10000; // 10 seconds
    bool gameOver;
    bool gameActive;
    bool newHighScore;
    bool firstScore;
    FinalScore *final;
    StartBtn *start_btn;
    RestartBtn *restart_btn;
    Player * player_ptr;


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
    QGraphicsPixmapItem* startScreenItem;

};

#endif // GAME_H
