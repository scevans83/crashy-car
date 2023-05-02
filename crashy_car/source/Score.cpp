#include "Score.h"
#include <QFont>
#include "Game.h"

extern Game * game;

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent){
    // initialize the score to 0
    score = 0;
    prevScore = 0;
    highScore = 0;

    // draw the text and rotate it
    setPlainText(QString("Score: ") + QString::number(score)); // Score: 0
    setDefaultTextColor(Qt::black);
    setPos(450, 0);
    setRotation(90);
}

void Score::increase(){
    score++;
    setPlainText(QString("Score: ") + QString::number(score)); // Score: 1
}

int Score::getScore(){
    return score;
}
int Score::getHighScore(){
    return highScore;
}

int Score::getPrevScore()
{
    return prevScore;
}


void Score::updateScore(int newScore)
{
    // Update the score
    score = newScore;

    // Update the text display
    setPlainText(QString("Score: ") + QString::number(score));
}

/* Resets the score to 0 when the 'Restart' button is pushed
   Also updates highScore if last round's score was higher than 
   previous high score */
void Score::scoreReset()
{
    prevScore = score;
    if (prevScore > highScore){
        highScore = prevScore;
        game->newHighScore = true;
    }
    score = 0;

}
