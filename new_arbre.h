#ifndef NEW_ARBRE_H
#define NEW_ARBRE_H
#include<QObject>
#include <QWidget>
#include<QMainWindow>
#include<QPushButton>
class new_arbre: public QWidget
{
    Q_OBJECT
public:
      new_arbre(QMainWindow*parent=0);
signals:

public slots:
    void create();
public:
    QPushButton*start_new;
    QMainWindow*mainWindow;
    QMainWindow*parent1;
};

#endif // NEW_ARBRE_H
