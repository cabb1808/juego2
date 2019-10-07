#include "personaje.h"
#include <math.h>
#include <cmath>
#include <QImage>
#include <QLabel>
#include <QGraphicsScene>
personaje::personaje(float posX_, float posY_, float velX_, float velY_, float masa_, float radio_, float K_, float e_)
{
    //declaramos el contructor para que entregue valores de todas las variables menos teta
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
    QImage image(":/images/ninja");
    QImage image2 = image.scaled(80, 80, Qt::KeepAspectRatio);
    QLabel *plotImg = new QLabel;
    plotImg->setScaledContents(true);
    setPixmap(QPixmap(QPixmap::fromImage(image2)));

}

personaje::~personaje()
{

}

float personaje::get_posX()
{
    return PosX;
}

float personaje::get_velY(){
    return VelY;
}

float personaje::get_masa(){
    return masa;
}

float personaje::get_e(){
    return e;
}

float personaje::get_posY(){                                    //
    return PosY;                                                //
}                                                               //
                                                                //
float personaje::get_Radio(){                                   //          FUNCIONES PARA DEVOLVER LOS
    return Rad;                                                 //           ATRIBUTOS PARA OPERAR CON
}                                                               //                       ELLOS
                                                                //
float personaje::get_velX(){                                    //
    return VelX;
}

void personaje::set_vel(float velx, float vely, float px, float py)   // Obtiene las posiciones anteriores
{                                                                     //    para actualizar la velocidad
    VelX = velx;                                                      //      y las posiciones actuales
    VelY = vely;
    PosX = px;
    PosY = py;
}

void personaje::actualizar2()                                                  // Actualiza respecto al tiempo la posicion
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
void personaje::setEscala(float s)
{
    escala=s;
}

QRectF personaje::boundingRect() const
{
    return QRectF(-1*escala*Rad,-1*escala*Rad,2*escala*Rad,2*escala*Rad);
}


void personaje::actualizar(float limitY)
{

    actualizar2();                  //actualiza las posiciones del cuerpo
    setPos(PosX,(limitY-PosY));  // actualiza posiciones en la interfaz
    QList<QGraphicsItem *> colliding_items =collidingItems();
    for (int i = 0, n = colliding_items.size();i<n;i++) {
        if(typeid(*(colliding_items[i])) == typeid(obstaculo)){
                set_vel(-1*get_e()*get_velX(),get_velY(), 50 ,150);
        }
        if(typeid(*(colliding_items[i])) == typeid(enemy))
        {
            scene()->removeItem(colliding_items[i]);
            delete colliding_items[i];
            set_vel(-1*get_e()*get_velX(),get_velY(), 50 ,150);
        }
    }
}


