#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <QLabel>

enemy::enemy()
{
    int random_number = rand() % 700;
    setPos(random_number,0);
    QImage image(":/images/arepa");
    QImage image2 = image.scaled(80, 80);
    QLabel *plotImg = new QLabel;
    plotImg->setScaledContents(true);
    setPixmap(QPixmap(QPixmap::fromImage(image2)));

    //Conexion
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(50);
}
void enemy::move()
{
    setPos(x(),y()+5);
    if(pos().y() < 0){
        scene()->removeItem(this);
        delete this;
    }
}
