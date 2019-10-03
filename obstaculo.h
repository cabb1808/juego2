#ifndef OBSTACULO_H
#define OBSTACULO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QGraphicsPixmapItem>
#include <QBrush>
#include <QImage>

class obstaculo : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit obstaculo(QObject *parent = nullptr);

signals:

public slots:
};

#endif // OBSTACULO_H
