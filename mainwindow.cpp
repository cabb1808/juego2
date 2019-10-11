#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>
#include <time.h>
#include <QKeyEvent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

        srand(time(NULL));
        ui->setupUi(this);
        limitX=1000;                   //Asigna el tamaño de la interfaz
        limitY=820;
        nivel();
        timer=new QTimer(this);                 //crea el timer
        timer2=new QTimer(this);
        timer3=new QTimer(this);
        timer4=new QTimer(this);
        connect(timer2,SIGNAL(timeout()),this,SLOT(spawn2()));
        connect(timer3,SIGNAL(timeout()),this,SLOT(spawn()));
        connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));
        timer2 -> start(3000);
        timer3 -> start(800);
        timer->start(6);

        QMediaPlayer * music = new QMediaPlayer();
        salto = new QMediaPlayer();

        music->setMedia(QUrl("qrc:/sounds/bgsound"));
        salto->setMedia(QUrl("qrc:/sounds/salto"));

        music->setVolume(10);
        music->play();


}

MainWindow::~MainWindow()
{
    delete timer;
    delete timer2;
    delete scene;
    delete ui;
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{

        // Utilizamos la funcion Set_vel de personaje para que cada vez que presione una tecla
        //           cambie su velocidad y le de un movimiento

        if (event->key() == Qt::Key_6 ){
            principal->set_vel(30,principal->get_velY(),principal->get_posX(), principal->get_posY());
        }
        if (event->key() == Qt::Key_4 ){
            principal->set_vel(-30,principal->get_velY(),principal->get_posX(), principal->get_posY());

        }
        if (event->key() == Qt::Key_8 && level==1 &&
             ((principal->get_posY()==limitY-655-principal->get_Radio() && principal->get_posX()>-100 &&
               principal->get_posX()<200-principal->get_Radio())
              ||(principal->get_posY()==limitY-635-principal->get_Radio() && principal->get_posX()>255-principal->get_Radio() && principal->get_posX()<395-principal->get_Radio())
              ||(principal->get_posY()==limitY-625-principal->get_Radio() && principal->get_posX()>425-principal->get_Radio() && principal->get_posX()<545-principal->get_Radio())
              ||(principal->get_posY()==limitY-575-principal->get_Radio() && principal->get_posX()>595-principal->get_Radio() && principal->get_posX()<760-principal->get_Radio())
              ||(principal->get_posY()==limitY-670-principal->get_Radio() && principal->get_posX()>800-principal->get_Radio() && principal->get_posX()<limitX-principal->get_Radio())
              ||(principal->get_posY()==limitY-410-principal->get_Radio())
              ||(principal->get_posY()==limitY-110-principal->get_Radio()))){
            principal->set_vel(principal->get_velX(),60,principal->get_posX(), principal->get_posY());
            salto->setVolume(10);
            salto->play();

        }
         if (event->key() == Qt::Key_8 && level==2 && ((principal->get_posY()==limitY-655-principal->get_Radio() && principal->get_posX()>-100 && principal->get_posX()<150-principal->get_Radio()) )){
             principal->set_vel(principal->get_velX(),60,principal->get_posX(), principal->get_posY());
             salto->setVolume(10);
             salto->play();
         }



}


void MainWindow::nivel()
{
    if(level==1){
        scene=new QGraphicsScene(this);         //crea la scene
        scene->setSceneRect(0,0,limitX,limitY); //establece el tamaño y posicion del scene

        scene->setBackgroundBrush(QBrush(QImage(":/images/fondo")));

        ui->graphicsView->setScene(scene);
        scene->addItem(fire);
        scene->addItem(fire2);
        scene->addItem(fire3);
        scene->addItem(fire4);


         principal->setEscala(5);


        ui->centralwidget->adjustSize();
        scene->addRect(scene->sceneRect());
        fire->setPos(360,765);
        fire2->setPos(500,765);
        fire3->setPos(170,765);
        fire4->setPos(725,765);

        ui->graphicsView->resize(scene->width(),scene->height());
        this->resize(ui->graphicsView->width()+100, ui->graphicsView->height()+100);
        principal->setFlag(QGraphicsItem::ItemIsFocusable);
        principal->setFocus();

        principal->actualizar(limitY);
        scene->addItem(principal);


    }
    else if(level==2){
        delete fire;
        delete fire2;
        delete fire3;
        delete fire4;
        scene=new QGraphicsScene(this);         //crea la scene
        scene->setSceneRect(0,0,limitX,limitY); //establece el tamaño y posicion del scene

        scene->setBackgroundBrush(QBrush(QImage(":/images/fondo2")));

        ui->graphicsView->setScene(scene);
        principal->setEscala(5);

        ui->centralwidget->adjustSize();
        scene->addRect(scene->sceneRect());

        ui->graphicsView->resize(scene->width(),scene->height());
        this->resize(ui->graphicsView->width()+100, ui->graphicsView->height()+100);
        principal->setFlag(QGraphicsItem::ItemIsFocusable);
        principal->setFocus();

        principal->actualizar(limitY);
        scene->addItem(principal);


    }
}
void MainWindow::actualizar()
{
        principal->actualizar(limitY);//actualiza en graf
        bordercollision(principal);//actualiza el choque con el borde
        if(level==2){
            for(int i=0;i<sierras.size();i++){
                sierras.at(i)->actualizar(limitY);
                bordercollision(sierras.at(i));
            }

        }
}

void MainWindow::spawn()
{

    if(level==1){
        enemy *enemigo1=new enemy();
        enemigos.push_back(enemigo1);
        scene->addItem(enemigos.back());

    }
    if(level==2){
        int random_number = rand() % 850;
        int random_number2 = rand() % 60;
        bola *sierra=new bola(random_number,350,random_number2,0,20,30,0.008,0.8);
        sierras.push_back(sierra);
        scene->addItem(sierras.back());
        sierras.back()->actualizar(limitY);
    }
}
void MainWindow::spawn2()
{

    if(level==1){
        enemy *enemigo2=new enemy(2);
        scene->addItem(enemigo2);
    }
    if(level==2){

    }
}

void MainWindow::bordercollision(personaje *b)//son los choques con los bordes
{
    if(b->get_posX()<0){
        b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 0, b->get_posY()) ;//con el borde izquierdo

    }
    if(b->get_posX()>limitX-b->get_Radio()){//posicion con el borde derecho.
        b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), limitX-25-b->get_Radio(), b->get_posY());
    }
    if(b->get_posY()< b->get_Radio()+25){//choque con el borde inferior.
        b->set_vel(b->get_velX(),-1*b->get_e()*b->get_velY(), (b->get_posX()), b->get_Radio()+25);
    }
    if(b->get_posY()>limitY){//choque con el borde superior.
        b->set_vel(b->get_velX(),-1*b->get_e()*b->get_velY(), b->get_posX(), limitY);
    }

    if(level==1){
        if(b->get_posX()>limitX-10-b->get_Radio()&& b->get_posY()>limitY-680-b->get_Radio() && b->get_posY()< limitY-600-b->get_Radio()){ //teleport
            b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 10, 450);
        }
        if(b->get_posX()>limitX-10-b->get_Radio()&& b->get_posY()>limitY-380-b->get_Radio() && b->get_posY()< limitY-300-b->get_Radio()){ //teleport
            b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 10, 750);
        }
        if(b->get_posX()>limitX-10-b->get_Radio()&& b->get_posY()>limitY-140-b->get_Radio() && b->get_posY()< limitY-60-b->get_Radio()){ //cambio level
            b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 10, 150);
            level=2;
            nivel();
        }
        if(b->get_posY()>limitY-190-b->get_Radio() && b->get_posY()<limitY-185-b->get_Radio()){
            b->set_vel(b->get_velX(),-1*b->get_e()*b->get_velY(), b->get_posX(), limitY-190-b->get_Radio());
        }                                                                                                          //tercera barra
        if(b->get_posY()<limitY-110-b->get_Radio() && b->get_posY()>limitY-120-b->get_Radio()){
            b->set_vel(b->get_velX(),-1*b->get_e()*b->get_velY(), b->get_posX(), limitY-110-b->get_Radio());
        }
        //
        if(b->get_posY()>limitY-490-b->get_Radio() && b->get_posY()<limitY-485-b->get_Radio()){
            b->set_vel(b->get_velX(),-1*b->get_e()*b->get_velY(), b->get_posX(), limitY-490-b->get_Radio());
        }                                                                                                          //Segunda barra
        if(b->get_posY()<limitY-410-b->get_Radio() && b->get_posY()>limitY-420-b->get_Radio()){
            b->set_vel(b->get_velX(),-1*b->get_e()*b->get_velY(), b->get_posX(), limitY-410-b->get_Radio());
        }
        // Primer Piso
        if(b->get_posX()>0 && b->get_posX()<3 && b->get_posY()<limitY-655-b->get_Radio() ){
            b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 0, b->get_posY());
        }
        if(b->get_posX()>190-b->get_Radio() && b->get_posX()<200-b->get_Radio() && b->get_posY()<limitY-655-b->get_Radio() ){
            b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 200-b->get_Radio(), b->get_posY());
        }
        if(b->get_posY()<limitY-655-b->get_Radio() && b->get_posX()>-100 && b->get_posX()<200-b->get_Radio()){
            b->set_vel(b->get_velX(),-1*b->get_e()*b->get_velY(), b->get_posX(),limitY-655-b->get_Radio());
         }

        if(b->get_posX()>255-b->get_Radio() && b->get_posX()<265-b->get_Radio() && b->get_posY()<limitY-635-b->get_Radio() ){
            b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 255-b->get_Radio(), b->get_posY());
        }
        if(b->get_posX()>390-b->get_Radio() && b->get_posX()<395-b->get_Radio() && b->get_posY()<limitY-635-b->get_Radio() ){
            b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 395-b->get_Radio(), b->get_posY());
        }
        if(b->get_posY()<limitY-635-b->get_Radio() && b->get_posX()>255-b->get_Radio() && b->get_posX()<395-b->get_Radio()){
            b->set_vel(b->get_velX(),-1*b->get_e()*b->get_velY(), b->get_posX(),limitY-635-b->get_Radio());
         }

        if(b->get_posX()>425-b->get_Radio() && b->get_posX()<430-b->get_Radio() && b->get_posY()<limitY-625-b->get_Radio() ){
            b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 425-b->get_Radio(), b->get_posY());
        }
        if(b->get_posX()>540-b->get_Radio() && b->get_posX()<545-b->get_Radio() && b->get_posY()<limitY-625-b->get_Radio() ){
            b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 545-b->get_Radio(), b->get_posY());
        }
        if(b->get_posY()<limitY-625-b->get_Radio() && b->get_posX()>425-b->get_Radio() && b->get_posX()<545-b->get_Radio()){
            b->set_vel(b->get_velX(),-1*b->get_e()*b->get_velY(), b->get_posX(),limitY-625-b->get_Radio());
         }

        if(b->get_posX()>595-b->get_Radio() && b->get_posX()<600-b->get_Radio() && b->get_posY()<limitY-575-b->get_Radio() ){
            b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 595-b->get_Radio(), b->get_posY());
        }
        if(b->get_posX()>750-b->get_Radio() && b->get_posX()<760-b->get_Radio() && b->get_posY()<limitY-575-b->get_Radio() ){
            b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 760-b->get_Radio(), b->get_posY());
        }
        if(b->get_posY()<limitY-575-b->get_Radio() && b->get_posX()>595-b->get_Radio() && b->get_posX()<760-b->get_Radio()){
            b->set_vel(b->get_velX(),-1*b->get_e()*b->get_velY(), b->get_posX(),limitY-575-b->get_Radio());
         }

        if(b->get_posX()>790-b->get_Radio() && b->get_posX()<810-b->get_Radio() && b->get_posY()<limitY-670-b->get_Radio() ){
            b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 800-b->get_Radio(), b->get_posY());
        }
        if(b->get_posY()<limitY-670-b->get_Radio() && b->get_posX()>800-b->get_Radio() && b->get_posX()<limitX-b->get_Radio()){
            b->set_vel(b->get_velX(),-1*b->get_e()*b->get_velY(), b->get_posX(),limitY-670-b->get_Radio());
        }

    }
    if(level==2){
        if(b->get_posX()>0 && b->get_posX()<3 && b->get_posY()<limitY-655-b->get_Radio() ){
            b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 0, b->get_posY());
        }
        if(b->get_posX()>140-b->get_Radio() && b->get_posX()<150-b->get_Radio() && b->get_posY()<limitY-655-b->get_Radio() ){
            b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 150-b->get_Radio(), b->get_posY());
        }
        if(b->get_posY()<limitY-655-b->get_Radio() && b->get_posX()>-100 && b->get_posX()<150-b->get_Radio()){
            b->set_vel(b->get_velX(),-1*b->get_e()*b->get_velY(), b->get_posX(),limitY-655-b->get_Radio());
         }
    }
}
void MainWindow::bordercollision(bola *b)//son los choques con los bordes
{
    if(b->get_posX()<0){
        b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 0, b->get_posY()) ;//con el borde izquierdo

    }
    if(b->get_posX()>limitX-b->get_Radio()){//posicion con el borde derecho.
        b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), limitX-25-b->get_Radio(), b->get_posY());
    }
    if(b->get_posY()< b->get_Radio()+25){//choque con el borde inferior.
        b->set_vel(b->get_velX(),-1*b->get_e()*b->get_velY(), (b->get_posX()), b->get_Radio()+25);
    }
    if(b->get_posY()>limitY){//choque con el borde superior.
        b->set_vel(b->get_velX(),-1*b->get_e()*b->get_velY(), b->get_posX(), limitY);
    }

    if(level==1){
        if(b->get_posX()>limitX-10-b->get_Radio()&& b->get_posY()>limitY-680-b->get_Radio() && b->get_posY()< limitY-600-b->get_Radio()){ //teleport
            b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 10, 450);
        }
        if(b->get_posX()>limitX-10-b->get_Radio()&& b->get_posY()>limitY-380-b->get_Radio() && b->get_posY()< limitY-300-b->get_Radio()){ //teleport
            b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 10, 750);
        }
        if(b->get_posX()>limitX-10-b->get_Radio()&& b->get_posY()>limitY-140-b->get_Radio() && b->get_posY()< limitY-60-b->get_Radio()){ //cambio level
            b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 10, 150);
            level=2;
            nivel();
        }
        if(b->get_posY()>limitY-190-b->get_Radio() && b->get_posY()<limitY-185-b->get_Radio()){
            b->set_vel(b->get_velX(),-1*b->get_e()*b->get_velY(), b->get_posX(), limitY-190-b->get_Radio());
        }                                                                                                          //tercera barra
        if(b->get_posY()<limitY-110-b->get_Radio() && b->get_posY()>limitY-120-b->get_Radio()){
            b->set_vel(b->get_velX(),-1*b->get_e()*b->get_velY(), b->get_posX(), limitY-110-b->get_Radio());
        }
        //
        if(b->get_posY()>limitY-490-b->get_Radio() && b->get_posY()<limitY-485-b->get_Radio()){
            b->set_vel(b->get_velX(),-1*b->get_e()*b->get_velY(), b->get_posX(), limitY-490-b->get_Radio());
        }                                                                                                          //Segunda barra
        if(b->get_posY()<limitY-410-b->get_Radio() && b->get_posY()>limitY-420-b->get_Radio()){
            b->set_vel(b->get_velX(),-1*b->get_e()*b->get_velY(), b->get_posX(), limitY-410-b->get_Radio());
        }
        // Primer Piso
        if(b->get_posX()>0 && b->get_posX()<3 && b->get_posY()<limitY-655-b->get_Radio() ){
            b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 0, b->get_posY());
        }
        if(b->get_posX()>190-b->get_Radio() && b->get_posX()<200-b->get_Radio() && b->get_posY()<limitY-655-b->get_Radio() ){
            b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 200-b->get_Radio(), b->get_posY());
        }
        if(b->get_posY()<limitY-655-b->get_Radio() && b->get_posX()>-100 && b->get_posX()<200-b->get_Radio()){
            b->set_vel(b->get_velX(),-1*b->get_e()*b->get_velY(), b->get_posX(),limitY-655-b->get_Radio());
         }

        if(b->get_posX()>255-b->get_Radio() && b->get_posX()<265-b->get_Radio() && b->get_posY()<limitY-635-b->get_Radio() ){
            b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 255-b->get_Radio(), b->get_posY());
        }
        if(b->get_posX()>390-b->get_Radio() && b->get_posX()<395-b->get_Radio() && b->get_posY()<limitY-635-b->get_Radio() ){
            b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 395-b->get_Radio(), b->get_posY());
        }
        if(b->get_posY()<limitY-635-b->get_Radio() && b->get_posX()>255-b->get_Radio() && b->get_posX()<395-b->get_Radio()){
            b->set_vel(b->get_velX(),-1*b->get_e()*b->get_velY(), b->get_posX(),limitY-635-b->get_Radio());
         }

        if(b->get_posX()>425-b->get_Radio() && b->get_posX()<430-b->get_Radio() && b->get_posY()<limitY-625-b->get_Radio() ){
            b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 425-b->get_Radio(), b->get_posY());
        }
        if(b->get_posX()>540-b->get_Radio() && b->get_posX()<545-b->get_Radio() && b->get_posY()<limitY-625-b->get_Radio() ){
            b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 545-b->get_Radio(), b->get_posY());
        }
        if(b->get_posY()<limitY-625-b->get_Radio() && b->get_posX()>425-b->get_Radio() && b->get_posX()<545-b->get_Radio()){
            b->set_vel(b->get_velX(),-1*b->get_e()*b->get_velY(), b->get_posX(),limitY-625-b->get_Radio());
         }

        if(b->get_posX()>595-b->get_Radio() && b->get_posX()<600-b->get_Radio() && b->get_posY()<limitY-575-b->get_Radio() ){
            b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 595-b->get_Radio(), b->get_posY());
        }
        if(b->get_posX()>750-b->get_Radio() && b->get_posX()<760-b->get_Radio() && b->get_posY()<limitY-575-b->get_Radio() ){
            b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 760-b->get_Radio(), b->get_posY());
        }
        if(b->get_posY()<limitY-575-b->get_Radio() && b->get_posX()>595-b->get_Radio() && b->get_posX()<760-b->get_Radio()){
            b->set_vel(b->get_velX(),-1*b->get_e()*b->get_velY(), b->get_posX(),limitY-575-b->get_Radio());
         }

        if(b->get_posX()>790-b->get_Radio() && b->get_posX()<810-b->get_Radio() && b->get_posY()<limitY-670-b->get_Radio() ){
            b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 800-b->get_Radio(), b->get_posY());
        }
        if(b->get_posY()<limitY-670-b->get_Radio() && b->get_posX()>800-b->get_Radio() && b->get_posX()<limitX-b->get_Radio()){
            b->set_vel(b->get_velX(),-1*b->get_e()*b->get_velY(), b->get_posX(),limitY-670-b->get_Radio());
        }

    }
    if(level==2){
        if(b->get_posX()>0 && b->get_posX()<3 && b->get_posY()<limitY-655-b->get_Radio() ){
            b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 0, b->get_posY());
        }
        if(b->get_posX()>140-b->get_Radio() && b->get_posX()<150-b->get_Radio() && b->get_posY()<limitY-655-b->get_Radio() ){
            b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), 150-b->get_Radio(), b->get_posY());
        }
        if(b->get_posY()<limitY-655-b->get_Radio() && b->get_posX()>-100 && b->get_posX()<150-b->get_Radio()){
            b->set_vel(b->get_velX(),-1*b->get_e()*b->get_velY(), b->get_posX(),limitY-655-b->get_Radio());
         }
    }
}
