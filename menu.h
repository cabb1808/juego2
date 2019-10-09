#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include "inicio.h"
namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Menu *ui;
    inicio *login;
};

#endif // MENU_H
