#include "Game.h"
#include "player.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QElapsedTimer>
#include <random>
#include "accelthread.h"
#include <QPushButton>
#include <QPropertyAnimation>


Game::Game(QWidget *parent){
    gameOver = false;
    gameActive = false;
    newHighScore = false;
    firstScore = true;

    // create the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,450,272);
    QImage bg_img(":/graphics/clippedRoad.jpg");
    bg_img = bg_img.scaled(272, 450, Qt::IgnoreAspectRatio, Qt::SmoothTransformation); // swap width and height
    bg_img = bg_img.mirrored(true, false); // flip horizontally
    bg_img = bg_img.transformed(QTransform().rotate(-90), Qt::SmoothTransformation); // rotate counterclockwise
    setBackgroundBrush(QBrush(bg_img));
    setScene(this->scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(450,272);

    //create player
    Player * player = new Player();
    player_ptr = player;
    scene->addItem(player);

    QImage ss_img(":/graphics/startLogo_resized");
    QPixmap startScreen = QPixmap::fromImage(ss_img);
    startScreenItem = new QGraphicsPixmapItem(startScreen);
    startScreenItem->setRotation(90);
    startScreenItem->setPos(465,0);
    scene->addItem(startScreenItem);

    start_btn = new StartBtn;
    scene->addItem(start_btn);

    restart_btn = new RestartBtn;
    scene->addItem(restart_btn);

    final = new FinalScore;
    scene->addItem(final);

    //create accelerometer thread
    AccelerometerThread *accelerometerThread = new AccelerometerThread(400, this);

    //connect xValueChanged signal to player's updatePlayerPosition slot
    QObject::connect(accelerometerThread, SIGNAL(xValueChanged(int)),
                        player, SLOT(updatePlayerPosition(int)));

    //start accelerometer thread
    accelerometerThread->start();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> obst1_dis(950,1750);
    std::uniform_int_distribution<> ls_dis(1500,3000);
    std::uniform_int_distribution<> rs_dis(1500,3000);
    obst_timer1_val = obst1_dis(gen);
    ls_cactus_val = ls_dis(gen);
    rs_cactus_val = rs_dis(gen);

    //spawn obstacle
    obst_timer1 = new QTimer;
    QObject::connect(obst_timer1, SIGNAL(timeout()), player, SLOT(spawn()));
    obst_timer1->start(obst_timer1_val);

    //spawn LeftSide and RightSide catci
    ls_cactus = new QTimer;
    QObject::connect(ls_cactus, SIGNAL(timeout()), player, SLOT(spawn_ls()));
    ls_cactus->start(ls_cactus_val);

    rs_cactus = new QTimer;
    QObject::connect(rs_cactus, SIGNAL(timeout()), player, SLOT(spawn_rs()));
    rs_cactus->start(rs_cactus_val);

    QTimer * linestimer = new QTimer;
    QObject::connect(linestimer,SIGNAL(timeout()),player,SLOT(lines()));
    linestimer->start(250);

    incr_diff_timer = new QTimer;
    QObject::connect(incr_diff_timer,SIGNAL(timeout()), player ,SLOT(updateTimers()));

    if(gameOver){
        linestimer->stop();
        obst_timer1->stop();
        ls_cactus->stop();
    }
    //score
    score = new Score();
    scene->addItem(score);
    score->setVisible(false);
    // Create a QElapsedTimer object to measure elapsed time
    QElapsedTimer checktimer;
    checktimer.start();

    // Create a QTimer object to increase the score every 0.1 seconds
    QTimer *scoreTimer = new QTimer(this);
    connect(scoreTimer, &QTimer::timeout, this, [checktimer, this]() mutable {
        if(gameActive && !gameOver){
            // Check if 0.1 seconds has elapsed
            if (checktimer.elapsed() >= 100) {
                // Reset the timer
                checktimer.restart();
                // Increase the score by 1
                score->increase();
            }
        }
    });
    scoreTimer->start(scoreInterval); // start the timer to trigger every 10 milliseconds
}

void Game::increaseScore() {
    // Increase the score by 1
    score->increase();

    // Adjust the interval of the score timer based on the current score
    if (score->getScore() % 10 == 0) { // check if the score is a multiple of 10
        scoreInterval *= 0.9; // decrease the interval by 10%
        QTimer *scoreTimer = qobject_cast<QTimer *>(sender());
        if (scoreTimer) { // check if the sender is a QTimer object
            scoreTimer->setInterval(scoreInterval); // set the new interval of the score timer
        }
    }
}

void Game::loser()
{
    score->setVisible(false);
    player_ptr->setPos(60, 136);
    player_ptr->setVisible(false);

    gameOver = true;
    restart_btn->setVisible(true);
    //restart_btn->text->setVisible(true);
    final->setVisible(true);
    final->score_text->setVisible(true);
    final->hs_text->setVisible(true);
    final->score = score->score;
    final->score_text->setPlainText(QString("Score: ")+ QString::number(final->score));
    score->scoreReset();
    if (final->score > final->high_score)
    {
        final->high_score = final->score;
        final->hs_text->setPlainText(QString("High Score: ")+ QString::number(final->high_score));
        final->hs_text->setVisible(false);
        final->new_hs_text->setVisible(true);
    }
    else
    {
        final->hs_text->setVisible(true);
        final->new_hs_text->setVisible(false);
    }
}

void Game::startGame()
{
    score->setVisible(true);
    gameActive = true;
    incr_diff_timer->start(incr_diff_timer_val);
    scene->removeItem(startScreenItem);
    player_ptr->setFocus();
}

void Game::restartGame()
{
    restart_btn->setVisible(false);
    //restart_btn->text->setVisible(false);
    final->setVisible(false);
    final->score_text->setVisible(false);
    final->hs_text->setVisible(false);
    final->new_hs_text->setVisible(false);
    score->setVisible(true);
    player_ptr->setVisible(true);
    player_ptr->setFocus();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> obst1_dis(950,1750);
    std::uniform_int_distribution<> ls_dis(1500,3000);
    std::uniform_int_distribution<> rs_dis(1500,3000);
    obst_timer1_val = obst1_dis(gen);
    ls_cactus_val = ls_dis(gen);
    rs_cactus_val = rs_dis(gen);
    obst_timer1->start(obst_timer1_val);
    ls_cactus->start(ls_cactus_val);
    rs_cactus->start(rs_cactus_val);
    incr_diff_timer_val = 10000;
    incr_diff_timer->start(incr_diff_timer_val);

    gameOver = false;
}
