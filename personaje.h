#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QObject>

class personaje : public QObject
{
    Q_OBJECT
public:
    explicit personaje(QObject *parent = nullptr);

signals:

public slots:
};

#endif // PERSONAJE_H
