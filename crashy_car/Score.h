#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score: public QGraphicsTextItem{
public:
    Score(QGraphicsItem * parent=0);
    void increase();
    int getScore();
    void updateScore(int newScore);
    void scoreReset();
    int getHighScore();
    int getPrevScore();
private:
    int score;
    int prevScore;
    int highScore;
};

#endif // SCORE_H
