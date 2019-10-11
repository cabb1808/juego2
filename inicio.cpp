#include "inicio.h"
#include "ui_inicio.h"
#include <QDebug>
#include <mainwindow.h>
inicio::inicio(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inicio)
{
    ui->setupUi(this);
    ui->graphicsView->setBackgroundBrush(QBrush(QImage(":/images/arepa")));
}

void inicio::sacarVector()
{
    ifstream archin;
    archin.open("Usuario.txt");
    string linea,usuario,contrasena;

    while(!archin.eof()){
        getline(archin,linea);
        for(int i=0;linea[i]!='\t';i++){
            usuario+=linea[i];
        }
    }

}

int inicio::buscarUsuario(string a,string b)
{
//    ofstream archof;
//    archof.open("Usuario.txt");
//    archof<<"carlos"<<'\t'<<"123"<<'&'<<char(10);
//    archof.close();
    ifstream archin;
    archin.open("Usuario.txt");
    string linea,usuario,contrasena;
    int i;
    while(!archin.eof()){
        i=0;
        getline(archin,linea);
        for(;linea[i]!='\t';i++){
            usuario+=linea[i];
        }
        i+=1;
        if(usuario==a){
            for(;linea[i]!='&';i++){

                contrasena+=linea[i];
            }
            if(contrasena==b){
                return 2;
            }
            else {
                return 1;
            }
        }
        else return 0;
    }
    archin.close();
}

void inicio::registrarUsuario(string a, string b)
{
    ofstream archof;
    archof.open("Usuario.txt",std::fstream::app);
    if(archof.is_open()){
        a=a+'\t'+b+'&';
        archof<<a<<char(10);
        //qDebug()<<"hola";
    }
    archof.close();
}

inicio::~inicio()
{
    delete ui;
}

void inicio::on_pushButton_clicked()
{
    string user=  (ui->UserName->text()). toStdString();
    string pass= ( ui->Password->text()). toStdString();
    if(buscarUsuario(user,pass)==0){
        ui->label_3->setText("Usuario no registrado");
        ui->UserName->clear();
        ui->Password->clear();
    }
    else if(buscarUsuario(user,pass)==1){
        ui->label_3->setText("Contraseña incorrecta");
        ui->Password->clear();
    }
    else if(buscarUsuario(user,pass)==2) {
        ingreso=1;
        MainWindow *w=new MainWindow;
        w->show();
        delete this;

    }
}

void inicio::on_pushButton_2_clicked()
{
    string user=  (ui->UserName->text()). toStdString();
    string pass= ( ui->Password->text()). toStdString();
    if(buscarUsuario(user)==1 ){
        ui->label_3->setText("Usuario ya registrado, ingrese sesion");

    }
    else if(buscarUsuario(user)==0 && user!=""){
        registrarUsuario(user,pass);
        ui->label_3->setText("Registrado Correctamente, ingrese sesion");
        ingreso=1;
    }
    qDebug()<<buscarUsuario(user);

}
