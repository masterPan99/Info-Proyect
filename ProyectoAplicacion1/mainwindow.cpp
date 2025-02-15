#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);//inicializa la parte grafica

    timeChange();
    //aqui se colocan los connects.
   // timer.start(1000);//1000ms =1s envia una señal cada 1 segundo
   // connect(ui->Inc_Level,SIGNAL(clicked()),this,SLOT(inc_tank_level()));//conexion de el boton incremento y una funcion slot.
   // connect(ui->SetLevelButt,SIGNAL(clicked()),this,SLOT());//conexion que recive un valor y lo setea en el tanque.
    connect(&timer,SIGNAL(timeout()),this,SLOT(Timer_Event()));//señal que llama a Timer_Event por cada segundo.
    //connect(ui->QinBtm,SIGNAL(clicked()),this,SLOT(TankIn()));//seteo un boton que carga datos, el boton se llama QinBtm;
    connect(ui->MaxBtm,SIGNAL(clicked()),this,SLOT(SetMax()));//boton que setea el valor maximo del tanque.
    connect(ui->SetTime,SIGNAL(clicked()),this,SLOT(timeChange()));//este es de pruebaaaaaaa hasta la aplicacion del qtimer
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
void MainWindow::inc_tank_level()//desarrollo de la funcion que inclementa nivel de tanque
{
    qDebug()<< "inc_tank_level() slot invoked";
    int current_level =ui->Tank->value();//extraigo valor del tanque
    ui->Tank->setValue (current_level);//incremento valor de tanque
}

void MainWindow::set_Tank_Level()//Proceso que setea un valor ingresado en el tanque
{
    bool ok;//para comprobar que se realizo bien la convercion de [chat --> int]
    QString str= ui->Inc_Level;// ejemplo de extraccion de texto de un Qline edit
    int value =str.toInt(&ok);//&ok el str to int requiere donde esta la memoria
    if(ok == true)
        ui->Tank->setValue(value);
    else
        QDebug()<< "Error converting to int";
}
*/
void MainWindow::Timer_Event()
{
    qDebug() <<"El Timer fue invocado";
    TankIn();
    Vacio();
    getValMAX();
}
int MainWindow::GetQin()
{
    bool ok;
    QString Caudalin = ui->Qin->text();//convierte a string el valor de la Qline Edit.
    int Caudal= Caudalin.toInt(&ok);//verifica la correcta conversion del Caudal a numero.
    if (ok==true)//verifico que se realizo correctamente la convercion.
    {
        //qDebug()<< "Este es el Caudal"<< Caudal;
        return Caudal;
    }
    else
        qDebug()<<"Error convert to int GetQin";

}

void MainWindow::TankIn()
{
    int dial = ui->Kin->value();//valor de la canilla.
   // qDebug() << "Este es el valor de Dial"<<dial;
    int aux= (GetQin()*dial)/100;//calculo procentual de caudal/apertura.
    int Tanklevel = ui->Tank->value();
    ui->Tank->setValue(Tanklevel + aux);
    if (Tanklevel==100)
    {
       // ui->full->setText("FULL");
    }
    int Aux= ui->Kin->value();           //creo un Auxiliar entero
    QString Kin = QString::number(Aux);  //Lo guardo en un QString
    ui->KOUTSVAL->setText(Kin);          //Lo muestro por pantalla.


}
int MainWindow::getValMAX()//extraigo valor del Qline Edit y lo transformo a entero
{
    bool ok;
    QString Valta =ui->TankCapacity->text();//valor del qlinedit del max valor de tanque
    int MAX= Valta.toInt(&ok);
    if(ok==true)
    {
        return MAX;
    }

}

void MainWindow::SetMax()
{
    ui->Tank->setMaximum(getValMAX());
    qDebug()<<"El valor maximo de Tanque es :"<<getValMAX();
}

//--------------------------salida de Tanque---------------------------------//
int MainWindow::Consumo()
{
    bool ok;
    QString VAL= ui->Qout->text();
    int val = VAL.toInt(&ok);
    if (ok==true)
    {
        return val;
    }
    else
        qDebug()<<"Error convert to inT VAL CONSUMO ";

}
void MainWindow::Vacio()
{
   int Dialout= ui->Kout->value();//extraigo valor del dial de Kout
   int aux= (Consumo()*Dialout)/100;//calculo procentual de caudal/apertura.
   int Tanklevel = ui->Tank->value();
   if (aux>Tanklevel)
   {
       ui->Tank->setValue(0);
   }
   ui->Tank->setValue(Tanklevel-aux);
   int Aux= ui->Kout->value();
   QString Kout = QString::number(Aux);
   ui->KOUTSVAL->setText(Kout);

}
//------------------------ Cambio de Tiempo ---------------------------------//

int MainWindow::NewTime()//extraigo valor del Qline Edit y lo transformo a entero
{
    bool ok;
    QString TIMER =ui->newtime->text();//valor del qlinedit del max valor de tanque
    int TimeN= TIMER.toInt(&ok);
    if(ok==true)
    {
        return TimeN;
    }
    else
        qDebug()<<"Error convert to int NewTime";

}/*
void MainWindow::timeChange()// intento de funcion que cabie manualmente el tiempo de trabajo del programa
{
    if(n==0)
    {
        timer.start(1000);
    }
    else
    {
       n=NewTime();
       timer.start(n);
    }

    qDebug() <<"Tiempo es ["<< n <<"]";
}*/
void MainWindow::timeChange()
{
    n = NewTime(); // Extrae el nuevo tiempo ingresado
    if(n > 0) // Asegúrate de que sea un valor válido
    {
        timer.start(n); // Reinicia el temporizador con el nuevo intervalo
        qDebug() <<"Tiempo actualizado a [" << n << "] ms";
    }
    else
    {
        qDebug() <<"Error: el tiempo ingresado no es válido.";
    }
}

//Observaciones Generales.
/*
  1_ Aplicar templates al codigo simplicaria la forma en la que se convierten valores a datos numericos
  , con ello, reduciendo 4 funciones a 1 gral.
  Por que no lo uso? simplemente por falta de practica con dicho tema.
*/
