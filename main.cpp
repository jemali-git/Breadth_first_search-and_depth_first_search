#include "graphwidget.h"
#include <QApplication>
#include <QTime>
#include <QMainWindow>
#include<QPushButton>
#include "QMPButton.h"
#include<QLabel>
#include<QThread>
#include<QWidget>
#include"new_arbre.h"
#include<QMainWindow>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QMainWindow mainWindow;
    mainWindow.setStyleSheet("background:rgb(124,135,131)");
    mainWindow.setFixedWidth(800);
    mainWindow.setFixedHeight(550);
    mainWindow.setWindowTitle("ARBRE ELASTIQUE");

     qsrand(QTime(4,3,10).secsTo(QTime::currentTime()));
      new_arbre*widget=new new_arbre(&mainWindow);
      widget->setGeometry(100,50,widget->width(),widget->height());

   mainWindow.show();

    return app.exec();
}
