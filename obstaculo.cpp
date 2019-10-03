#include "obstaculo.h"

obstaculo::obstaculo(int a, int b,QObject *parent) : QObject(parent)
{
    QImage image(":/images/fire");
    QImage image2 = image.scaled(a, b);
    QLabel *plotImg = new QLabel;
    plotImg->setScaledContents(true);
    setPixmap(QPixmap(QPixmap::fromImage(image2)));
}
