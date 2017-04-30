#include"QMPButton.h"
#include<QPixmap>

QMPButton::QMPButton(const QString &description,QObject *parent) :

QPushButton(description,(QPushButton*)parent)

{
    setFixedSize(60,30);
    setStyleSheet("background:rgb(87,87,87);color:white; font: 12px arial, sans-serif;");
}
