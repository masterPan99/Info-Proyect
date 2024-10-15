#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int n=1000;

private:
    Ui::MainWindow *ui;
    QTimer timer;

public slots:
   /* void inc_tank_level();//funcion que incrementa el nivel de tanque
    void set_Tank_Level();//setea nivel de tanque*/
    void Timer_Event();//Avisa que incrementa el tiempo.
    int GetQin();//esta funcion devuelve el valor de la Caudal de entrada (Qin).
    void TankIn();//Funcion que relaciona el llenado de tanque, la apertura de a canilla y el caudal de Disponible.
    int getValMAX();
    void SetMax();
    int Consumo();
    void Vacio();
    int NewTime();
    void timeChange();
};
#endif // MAINWINDOW_H
