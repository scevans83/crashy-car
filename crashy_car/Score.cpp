#include "Score.h"
#include <QFont>

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent){
    // initialize the score to 0
    score = 0;
    prevScore = 0;
    highScore = 0;

    // draw the text
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

void Score::updateScore(int newScore)
{
    // Update the score
    score = newScore;

    // Update the text display
    setPlainText(QString("Score: ") + QString::number(score));
}

void Score::scoreReset()
{
    prevScore = score;
    if (prevScore > highScore){
        highScore = prevScore;
        newHighScore = true;
    }
    score = 0;

}
