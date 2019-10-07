#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QImage>

class enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enemy(int tipe=1);

    int getTipo() const;

private:
    int tipo;
signals:

public slots:
    void move();
};

#endif // ENEMY_H
