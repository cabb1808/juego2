#include "bola.h"
#include <math.h>
#include <cmath>
#include <QImage>
#include <QLabel>
#include <QGraphicsScene>
bola::bola(float posX_, float posY_, float velX_, float velY_, float masa_, float radio_, float K_, float e_)
{
    PosX = posX_;
    PosY = posY_;
    masa = masa_;
    Rad = radio_+10;
    VelX = velX_;
    VelY = velY_;
    AceX = 0;
    AceY = 0;
    G = 10;
    K = K_;
    e = e_;
    V = 0;
    dt = 0.1;
    escala=1;
        QImage image(":/images/sierra");
        QImage image2 = image.scaled(40, 40, Qt::KeepAspectRatio);
        QLabel *plotImg = new QLabel;
        plotImg->setScaledContents(true);
        setPixmap(QPixmap(QPixmap::fromImage(image2)));
    QTimer *timer=new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(vidaMas()));
    timer->start(20);
}
float bola::get_posX()
{
    return PosX;
}

float bola::get_velY(){
    return VelY;
}

float bola::get_masa(){
    return masa;
}

float bola::get_e(){
    return e;
}

float bola::get_posY(){                                    //
    return PosY;                                                //
}                                                               //
                                                                //
float bola::get_Radio(){                                   //          FUNCIONES PARA DEVOLVER LOS
    return Rad;                                                 //           ATRIBUTOS PARA OPERAR CON
}                                                               //                       ELLOS
                                                                //
float bola::get_velX(){                                    //
    return VelX;
}

void bola::set_vel(float velx, float vely, float px, float py)   // Obtiene las posiciones anteriores
{                                                                     //    para actualizar la velocidad
    VelX = velx;                                                      //      y las posiciones actuales
    VelY = vely;
    PosX = px;
    PosY = py;
}

void bola::actualizar2()                                                  // Actualiza respecto al tiempo la posicion
                                                                              //    velocidad, angulo y aceleracion para el
{                                                                             //      siguiente instante
    V = pow(((VelX*VelX)+(VelY*VelY)),1/2);             // √(Vx)² + (Vy)²
    teta = atan2(VelY,VelX);                            // arctan(Vy/Vx)

    AceX = -((K*(V*V)*(Rad*Rad))/masa)*cos(teta);       // -kV²R²Cos(θ)/m
    AceY = (-((K*(V*V)*(Rad*Rad))/masa)*sin(teta))-G;   // -kV²R²Cos(θ)/m - g

    PosX = PosX + (VelX*dt) +((AceX*(dt*dt))/2);        // x+Vxt+(1/2)at²
    PosY = PosY + (VelY*dt) +((AceY*(dt*dt))/2);        // y+Vyt+(1/2)at²

    VelX = VelX + (AceX*dt);                              // Vxt+at
    VelY = VelY + (AceY*dt);                              // Vyt+at
}


// Aqui empiezan las funciones para graficarlo
void bola::setEscala(float s)
{
    escala=s;
}

QRectF bola::boundingRect() const
{
    return QRectF(-1*escala*Rad,-1*escala*Rad,2*escala*Rad,2*escala*Rad);
}


void bola::actualizar(float limitY)
{

    actualizar2();                  //actualiza las posiciones del cuerpo
    setPos(PosX,(limitY-PosY));  // actualiza posiciones en la interfaz
    if(vida>10) delete this;
}


int bola::getVida() const
{
    return vida;
}

void bola::setVida(int value)
{
    vida = value;
}

void bola::vidaMas()
{
    vida=vida+1;
}

