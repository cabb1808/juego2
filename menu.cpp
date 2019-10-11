#include "menu.h"
#include "ui_menu.h"


Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    login=new inicio;
}

Menu::~Menu()
{
    delete ui;
}


void Menu::on_pushButton_clicked()
{  
    login->show();
}

void Menu::on_pushButton_2_clicked()
{
    MainWindow *w=new MainWindow;
    w->show();
}
