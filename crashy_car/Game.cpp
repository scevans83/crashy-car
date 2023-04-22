#include "Game.h"
#include "player.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QElapsedTimer>
#include "accelthread.h"
#include <QPushButton>


Game::Game(QWidget *parent){
    gameOver = false;
    gameActive = false;
    // create the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,450,272);
    QImage bg_img(":/graphics/clippedRoad.jpg");
    bg_img = bg_img.scaled(272, 450, Qt::IgnoreAspectRatio, Qt::SmoothTransformation); // swap width and height, adjust scaling factor as needed
    bg_img = bg_img.mirrored(true, false); // flip horizontally
    bg_img = bg_img.transformed(QTransform().rotate(-90), Qt::SmoothTransformation); // rotate counterclockwise
    setBackgroundBrush(QBrush(bg_img));
    setScene(this->scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(450,272);

    //create player
    Player * player = new  Player();
    QPixmap car_orig(":/graphics/car.png");
    QPixmap car_img = car_orig.scaled(QSize(25,50));
    player->setPixmap(car_img);
    player->setPos(60, 136);
    player->setRotation(90);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);

    // Create start button
    QPushButton* startButton = new QPushButton("Start");
    startButton->setGeometry(200, 100, 100, 50);
    startButton->setStyleSheet("font-size: 20px; color: white; background-color: green; border: none;");

    // Add start button to the scene
    scene->addWidget(startButton);

    // Connect start button clicked signal to a lambda function that starts the game
    QObject::connect(startButton, &QPushButton::clicked, this, [this, startButton, player]() {
        startButton->hide();
        startGame();
        player->setFocus();
    });

    // Create start button
    replayButton = new QPushButton("Restart");
    replayButton->setGeometry(200, 100, 100, 50);
    replayButton->setStyleSheet("font-size: 20px; color: white; background-color: blue; border: none;");

    // Add start button to the scene
    scene->addWidget(replayButton);
    replayButton->setVisible(gameOver);

    // Connect start button clicked signal to a lambda function that starts the game
    QObject::connect(replayButton, &QPushButton::clicked, this, [this, player]() {
        replayButton->hide();
        restartGame();
        player->setFocus();

    });


    //create accelerometer thread
    //AccelerometerThread *accelerometerThread = new AccelerometerThread(400, this);

    // connect xValueChanged signal to player's updatePlayerPosition slot
    //QObject::connect(accelerometerThread, SIGNAL(xValueChanged(int)),
    //                 player, SLOT(updatePlayerPosition(int)));

    //start accelerometer thread
    //accelerometerThread->start();

    //create roadlines
    RoadLines *lines = new RoadLines();
    lines->setPos(485, 136); // set the initial position of the RoadLines object
    scene->addItem(lines);

    //spawn obstacle
    QTimer * timer = new QTimer;
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(spawn()));
    timer->start(2500);

    QTimer * linestimer = new QTimer;
    QObject::connect(linestimer,SIGNAL(timeout()),player,SLOT(lines()));
    linestimer->start(500);

    if(gameOver){
        linestimer->stop();
        timer->stop();
    }
    //score
    score = new Score();
    scene->addItem(score);
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
    gameOver = true;
    replayButton->setVisible(gameOver);
    score->scoreReset();

}


void Game::startGame()
{
    gameActive = true;
}

void Game::restartGame()
{
    gameOver = false;
}
