#ifndef INICIO_H
#define INICIO_H

#include <QWidget>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

namespace Ui {
class inicio;
}

class inicio : public QWidget
{
    Q_OBJECT

public:
    explicit inicio(QWidget *parent = nullptr);
    void sacarVector();
    int buscarUsuario(string a,string b="*****");
    void registrarUsuario(string a,string b);
    ~inicio();
    int ingreso=0;
private slots:
    void on_pushButton_clicked();


    void on_pushButton_2_clicked();

private:
    Ui::inicio *ui;
    vector<pair<string,string>> usuarios;
};

#endif // INICIO_H
