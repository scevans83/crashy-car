#include <QApplication>
#include <QGraphicsScene>
#include "MyRect.h"
#include <QGraphicsView>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //create a scene
    QGraphicsScene * scene = new QGraphicsScene();

    //create an item
    MyRect * player = new MyRect();
    player->setRect(0,0,100,100);

    //add item to scene
    scene->addItem(player);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    //add view
    QGraphicsView * view = new QGraphicsView(scene);

    view->setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(800,600);
    scene->setSceneRect(0,0,800,600);

    player->setPos((view->width()/2)+30,(view->height()-player->rect().height())-50);

    view->show();

    //spawn obstacle
    QTimer * timer = new QTimer;
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(spawn()));
    timer->start(2000);


    return a.exec();
}
