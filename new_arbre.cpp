#include "new_arbre.h"
#include "graphwidget.h"
#include <QApplication>
#include <QTime>
#include <QMainWindow>
#include<QPushButton>
#include "QMPButton.h"
#include<QLabel>
#include<QThread>


new_arbre::new_arbre(QMainWindow*parent):
    QWidget(parent)
{
    parent1=parent;
    setFixedHeight(400);
    setFixedWidth(600);
   /* dispaly=new QLabel(this);
    dispaly->setGeometry(250,0,200,70);
    dispaly->setText(QString::number(node_list.size()));
    dispaly->setStyleSheet("background:transparent;color: rgb(0,0,0,150); font-size: 80px;");
    dispaly->setAlignment(Qt::AlignCenter);
*/
    start_new=new QPushButton("START",this);
    start_new->setStyleSheet("background:rgb(100,110,110);color: black; font-size: 50px;");
    start_new->setGeometry(200,250,200,100);
    connect(start_new,SIGNAL(clicked()),this,SLOT(create()));

}
void new_arbre::create()
{
    parent1->hide();
    GraphWidget *widget = new GraphWidget;
    QMainWindow*mainWindow=new QMainWindow(this);
    mainWindow->setStyleSheet("background:rgb(255,255,255)");
    mainWindow->setCentralWidget(widget);
    mainWindow->setFixedWidth(700);
    mainWindow->setFixedHeight(550);
     //mainWindow->setGeometry(0,0,600,400);

    QMPButton*NEW=new QMPButton("nouveau",mainWindow);
    NEW->setToolTip("creer un nouvel arbre");
    QMPButton*BFS=new QMPButton("bfs",mainWindow);
    BFS->setToolTip("parcours en largeur");
    QMPButton*DFS=new QMPButton("dfs",mainWindow);
    DFS->setToolTip("parcours en profondeur");
    QMPButton*DELETE=new QMPButton("supprimer \n tout",mainWindow);
    DELETE->setToolTip("supprimer tous") ;
    QMPButton*EXIT=new QMPButton("quitter",mainWindow);
    EXIT->setToolTip("quitter l'application");

    NEW->setGeometry(40,80,NEW->width(),NEW->height());

    BFS->setGeometry(40,120,BFS->width(),BFS->height());
    DFS->setGeometry(40,160,DFS->width(),DFS->height());

    DELETE->setGeometry(40,200,DELETE->width(),DELETE->height());
    EXIT->setGeometry(40,240,EXIT->width(),EXIT->height());



    QMainWindow::connect(EXIT,SIGNAL(clicked()), QCoreApplication::instance(),SLOT(quit()));

    QMainWindow::connect(DELETE,SIGNAL(clicked()),widget,SLOT(del_all()));

    QMainWindow::connect(NEW,SIGNAL(clicked()),widget,SLOT(new_tree()));
    QMainWindow::connect(NEW,SIGNAL(hovered()),NEW,SLOT(show_text()));

    QMainWindow::connect(BFS,SIGNAL(clicked()),widget,SLOT(BFS()));

    QMainWindow::connect(DFS,SIGNAL(clicked()),widget,SLOT(DFS()));

    mainWindow->show();
}
