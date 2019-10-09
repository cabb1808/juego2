#include "inicio.h"
#include "ui_inicio.h"
#include <QDebug>
inicio::inicio(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inicio)
{
    ui->setupUi(this);
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
    ifstream archin;
    archin.open("Usuario.txt");
    string linea,usuario,contrasena;
    int i;
    while(!archin.eof()){
        i=0;
        getline(archin,linea);
        for(;linea[i]!=9;i++){
            usuario+=linea[i];
        }
        i+=1;
        if(usuario==a){
            for(;linea[i]!='&';i++){

                contrasena+=linea[i];
            }
            if(contrasena==b){
                return "Bien";
            }
            else {
                return "Mal";
            }
        }
        else return "Nada";
    }
    archin.close();
}

inicio::~inicio()
{
    delete ui;
}

void inicio::on_pushButton_clicked()
{
    string user=  (ui->UserName->text()). toStdString();
    string pass= ( ui->Password->text()). toStdString();
    qDebug()<<QString::fromStdString(buscarUsuario(user,pass));
    //ui->label_3->setText(buscarUsuario(user,pass));
}
