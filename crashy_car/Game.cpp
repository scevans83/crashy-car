#include "Game.h"
#include "player.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QElapsedTimer>
#include <random>
#include "accelthread.h"
#include <QPushButton>


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
    QPixmap car_orig(":/graphics/car.png");
    QPixmap car_img = car_orig.scaled(QSize(25,50));
    player->setPixmap(car_img);
    player->setPos(60, 136);
    player->setRotation(90);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();    
    QRectF playerBounds = player->boundingRect();
    playerBounds.adjust(20,20,-20,-20);
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
    replayButton->setGeometry(sceneRect().width() / 2 - replayButton->width() / 2,
                              sceneRect().height() / 2 - replayButton->height() / 2,
                              replayButton->width(),
                              replayButton->height());
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
    AccelerometerThread *accelerometerThread = new AccelerometerThread(400, this);

    //connect xValueChanged signal to player's updatePlayerPosition slot
    QObject::connect(accelerometerThread, SIGNAL(xValueChanged(int)),
                        player, SLOT(updatePlayerPosition(int)));

    //start accelerometer thread
    accelerometerThread->start();

    //create roadlines
    RoadLines *lines = new RoadLines();
    lines->setPos(485, 136); // set the initial position of the RoadLines object
    scene->addItem(lines);

    //spawn obstacle
    obst_timer1 = new QTimer;
    obst_timer2 = new QTimer;
    QObject::connect(obst_timer1, SIGNAL(timeout()), player, SLOT(spawn()));
    QObject::connect(obst_timer2, SIGNAL(timeout()), player, SLOT(spawn()));
    obst_timer1->start(950);
    obst_timer2->start(1650);

    //spawn LeftSide trees
    ls_tree = new QTimer;
    QObject::connect(ls_tree, SIGNAL(timeout()), player, SLOT(spawn_ls()));
    ls_tree->start(3000);

    QTimer * linestimer = new QTimer;
    QObject::connect(linestimer,SIGNAL(timeout()),player,SLOT(lines()));
    linestimer->start(250);

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

    //score display

    scoreLabel = new QLabel("Score: 0"); // Create a new QLabel object
    scoreLabel->setGeometry(50, 50, 100, 50);
    scoreLabel->setStyleSheet("font-size: 20px; color: white; background-color: black; border-radius: 10px; padding: 5px; border: 1px solid gray;");
    scoreLabel->setVisible(false); // Set initial visibility to false
    scoreLabel->setAlignment(Qt::AlignCenter);
    scene->addWidget(scoreLabel);

    highScoreLabel = new QLabel("High Score: 0"); // Create a new QLabel object
    highScoreLabel->setGeometry(250, 50, 120, 50);
    highScoreLabel->setStyleSheet("font-size: 20px; color: white; background-color: black; border-radius: 10px; padding: 5px; border: 1px solid gray;");
    highScoreLabel->setVisible(false); // Set initial visibility to false
    highScoreLabel->setAlignment(Qt::AlignCenter);
    highScoreLabel->setWordWrap(true);
    scene->addWidget(highScoreLabel);

    newHighScoreLabel = new QLabel("New High Score!\n0"); // Create a new QLabel object
    newHighScoreLabel->setGeometry(250, 50, 100, 50);
    newHighScoreLabel->setGeometry(sceneRect().width() / 2 - newHighScoreLabel->width() / 2,
                                   sceneRect().height() / 2 - newHighScoreLabel->height() / 2,
                                   newHighScoreLabel->width(),
                                   newHighScoreLabel->height());
    newHighScoreLabel->setStyleSheet("font-size: 20px; color: white; background-color: black; border-radius: 10px; padding: 5px; border: 1px solid gray;");
    newHighScoreLabel->setVisible(false); // Set initial visibility to false
    newHighScoreLabel->setAlignment(Qt::AlignCenter);
    newHighScoreLabel->setWordWrap(true);
    scene->addWidget(newHighScoreLabel);
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
    if(!newHighScore || firstScore){
        scoreLabel->setText("Score: " + QString::number(score->getPrevScore()));
        scoreLabel->setVisible(true);
        highScoreLabel->setText("High Score:\n" + QString::number(score->getHighScore()));
        highScoreLabel->setVisible(true);
        if (firstScore)
            firstScore = false;
    }
    else {
        scoreLabel->setText("New High Score!\n" + QString::number(score->getPrevScore()));
        scoreLabel->setVisible(true);
        newHighScore = false;
    }
}

void Game::startGame()
{
    gameActive = true;
}

void Game::restartGame()
{
    gameOver = false;
    scoreLabel->setVisible(false);
    highScoreLabel->setVisible(false);

}
