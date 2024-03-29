#ifndef BOLA_H
#define BOLA_H
#include "personaje.h"
#include <QPainter>
#include "obstaculo.h"
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <stdlib.h>
#include <time.h>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QObject>
#include "enemy.h"
class personaje;

class bola : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    bola(float posX_, float posY_, float velX_, float velY_, float masa_, float radio_, float K_, float e_);
    float get_posX();
    float get_posY();
    float get_Radio();
    float get_e();
    float get_velX();
    float get_velY();
    float get_masa();
    void set_vel(float velx, float vely, float px, float py);
    void actualizar2();
    // Aqui empiezan las funciones para graficarlo
    void setEscala(float s);
    QRectF boundingRect() const; // Monitor dice que es necesario
    void actualizar(float vel_Limit);
    void unSpawn();

    int getVida() const;

    void setVida(int value);
    void vidaMas();

public slots:
private:


    float PosX ;    //Posicion en x
    float PosY;     //posicion en y
    float masa;     //masa del cuerpo
    float Rad;      //radio del cuerpo
    float VelX;     //velocidad en x
    float VelY;     //velocidad en y
    float teta;     //angulo en el que va el cuerpo.
    float AceX;     //aceleracion en x
    float AceY;     //aceleracion en y
    float G;        //gravedad
    float K;        //resistencia del aire
    float e;        //coeficiente de restitucion.
    float V;        //Magnitud del vector velocidad
    float dt;       //delt a de tiempo.
    float escala = 1;   //Escala de grafica
    int vida=0;
};

#endif // BOLA_H
