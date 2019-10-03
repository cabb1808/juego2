#include "obstaculo.h"

obstaculo::obstaculo(QObject *parent) : QObject(parent)
{
    QImage image(":/images/fire");
    QImage image2 = image.scaled(50, 50, Qt::KeepAspectRatio);
    QLabel *plotImg = new QLabel;
    plotImg->setScaledContents(true);
    setPixmap(QPixmap(QPixmap::fromImage(image2)));
}
