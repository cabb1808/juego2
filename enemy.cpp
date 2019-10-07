#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <QLabel>

enemy::enemy(int tipe)
{
    tipo=tipe;
    if(tipo==1){
        int random_number = rand() % 850;
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
    else if(tipo==2){
        setPos(800,450);
        QLabel *plotImg = new QLabel;
        plotImg->setScaledContents(true);
        setPixmap(QPixmap(":/images/malo"));

        //Conexion
        QTimer * timer = new QTimer();
        connect(timer,SIGNAL(timeout()),this,SLOT(move()));
        timer->start(50);
    }
}

int enemy::getTipo() const
{
    return tipo;
}
void enemy::move()
{
    if(tipo==1){
        setPos(x(),y()+5);
        if(pos().y() > 150){
            //scene()->removeItem(this);
            delete this;
        }
    }
    else if(tipo==2){
        setPos(x()-5,y());
        if(pos().x() < 150){
            //scene()->removeItem(this);
            delete this;
        }
    }
}
