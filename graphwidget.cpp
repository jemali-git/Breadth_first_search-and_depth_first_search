#include "graphwidget.h"
#include "edge.h"
#include "node.h"
#include <math.h>
#include<QTime>
#include<QEventLoop>
#include<QList>
#include<QObject>


GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent)
{

    QGraphicsScene*scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-200, -200, 400, 400);

    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(10);
    pen.setBrush(QColor(194,194,194));
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    scene->addRect(QRectF(-200, -200, 400, 400),pen,QColor(255,255,255));
    scene->setSceneRect(-200, -200, 400, 400);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(FullViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(1), qreal(1));
    setMinimumSize(400, 400);
    setWindowTitle(tr("arbre elastiques"));

    timerId = startTimer(25);

    table_color.push_back(QColor(255,0,0));
    table_color.push_back(QColor(0,0,255));
    table_color.push_back(QColor(255,255,0));
    table_color.push_back(QColor(0,255,255));
    table_color.push_back(QColor(255,0,255));
    table_color.push_back(QColor(192,192,192));
    table_color.push_back(QColor(128,128,0));
    table_color.push_back(QColor(0,128,128));
    table_color.push_back(QColor(255,180,193));
    table_color.push_back(QColor(47,79,79));
    table_color.push_back(QColor(188,143,143));
    table_color.push_back(QColor(210,105,30));


    dispaly=new QLabel(this);
    dispaly->setGeometry(250,0,200,70);
    dispaly->setText(QString::number(node_list.size()));
    dispaly->setStyleSheet("background:transparent;color: rgb(0,0,0,150); font-size: 80px;");
    dispaly->setAlignment(Qt::AlignCenter);

    new_tree1=add_node1=BFS1=DFS1=del_node1=del_all1=0;

    test=new int;
    *test=0;
}
GraphWidget::~GraphWidget()
{
    killTimer(timerId);
}

void GraphWidget::new_tree()
{
    if(!(new_tree1||add_node1||BFS1||DFS1||del_node1||del_all1))
    {
        new_tree1=1;
    centerNode = new Node(this);

    centerNode->size=0;
    double opacity=0;
    centerNode->setOpacity(opacity);

    scene()->addItem(centerNode);
    centerNode->setPos(20, 40);
    centerNode->couleur=table_color[0];
    centerNode->aux_couleur=centerNode->couleur;

    QSound new_sound(":/sound/new_sound.wav");

    new_sound.play();
    for(int i=0;i<20;i++)
    {
       opacity+=0.05;
       centerNode->setOpacity(opacity);
       centerNode->size+=1;
       centerNode->update();
       scene()->update();
       delay(0.05);
    }
    centerNode->size=20;
    centerNode->setOpacity(1);
    centerNode->parent=0;
    node_list<<centerNode;
    connect(centerNode, SIGNAL(node_click_right(Node*)),this,SLOT(add_node(Node*)));
    connect(centerNode, SIGNAL(node_click_left(Node*)),this,SLOT(del_node(Node*)));

    dispaly->setText(QString::number(node_list.size()));
    new_tree1=0;
    }
    else
        return;
}

void GraphWidget::add_node(Node*source_node)
{
    if(!(new_tree1||add_node1||BFS1||DFS1||del_node1||del_all1))
    {
        add_node1=1;

        Node *new_node = new Node(this);

        new_node->parent=source_node;
        source_node->children_list<<new_node;
        node_list<<new_node;

        int rgb= table_color.indexOf(source_node->couleur);
        if(rgb<table_color.size()-2)
        new_node->couleur=table_color[rgb+1];
        else
            new_node->couleur=QColor(255,255,255);
         new_node->aux_couleur=new_node->couleur;
        new_node->size=0;

        double opacity=0;
        new_node->setOpacity(opacity);

        scene()->addItem(new_node);
        new_node->setPos(20, 200);
        scene()->addItem(new Edge( source_node,new_node));

        QSound new_sound(":/sound/new_sound.wav");
        new_sound.play();
        for(int i=0;i<20;i++)
        {
           opacity+=0.05;
           new_node->setOpacity(opacity);
           new_node->size+=1;
           new_node->update();
           scene()->update();
           delay(0.05);
        }
        new_node->size=20;
        new_node->setOpacity(1);

        connect(new_node, SIGNAL(node_click_right(Node*)),this,SLOT(add_node(Node*)));
        connect(new_node, SIGNAL(node_click_left(Node*)),this,SLOT(del_node(Node*)));

        dispaly->setText(QString::number(node_list.size()));

        add_node1=0;
        }
    else
        return;
}

void GraphWidget::BFS()
{
    if(!(new_tree1||add_node1||BFS1||DFS1||del_node1||del_all1))
    {
        BFS1=1;
    QSound BFS_sound(":/sound/D_BFS_sound.wav");

    if(!node_list.isEmpty())
    {
    QList<Node*> node_fil;
    Node*aux;
    node_fil<< node_list[0];
    node_fil[0]->couleur=Qt::gray;
    BFS_sound.play();

    node_fil[0]->update();
    scene()->update();
    while(!node_fil.isEmpty())
    {
        delay(1);
        aux=node_fil.last();
        if(!aux->children_list.isEmpty())
        {
            delay(1);
            foreach(Node*var1,aux->children_list)
            {
                node_fil.push_front(var1);
               var1->couleur=Qt::gray;
               BFS_sound.play();

                var1->update();
                scene()->update();
                delay(1);
            }
        }
        node_fil.pop_back();
        aux->couleur=Qt::black;
        BFS_sound.play();
        aux->update();
        scene()->update();

    }
    delay(1);
    QSound change_all(":/sound/change_all.wav");
    change_all.play();
    foreach (Node* var1 , node_list)
    {


             var1->couleur=var1->aux_couleur;
             var1->update();
             scene()->update();
    }
    delay(1);
   }
    BFS1=0;
    }
    else
        return;
}

void GraphWidget::DFS()
{
    if(!(new_tree1||add_node1||BFS1||DFS1||del_node1||del_all1))
    {
        DFS1=1;
    QSound DFS_sound(":/sound/D_BFS_sound.wav");
    if(!node_list.isEmpty())
    {
        QList<Node*> node_pile;
        Node*aux;
        int test;
        node_pile<< node_list[0];
        node_pile[0]->couleur=Qt::gray;
        DFS_sound.play();
        node_pile[0]->update();
        scene()->update();
        while(!node_pile.isEmpty())
        {
            delay(1);
            aux=node_pile.last();
            if(!aux->children_list.isEmpty())
            {
                test=0;
                foreach(Node*var1,aux->children_list)
                {
                    if(!(var1->couleur==Qt::gray||var1->couleur==Qt::black))
                    {   delay(1);
                        node_pile.push_back(var1);
                        var1->couleur=Qt::gray;
                        var1->update();
                        scene()->update();
                        DFS_sound.play();
                        test=1;
                        break;
                    }
                }
                if(test==0)
                {
                    delay(1);
                    node_pile.pop_back();
                    aux->couleur=Qt::black;
                    DFS_sound.play();
                    aux->update();
                    scene()->update();
                }
            }
            else
            {
                delay(1);
                aux->couleur=Qt::black;
                DFS_sound.play();
                aux->update();
                scene()->update();
                node_pile.pop_back();
            }
        }
        delay(1);
        QSound change_all(":/sound/change_all.wav");
        change_all.play();
        foreach (Node* var1 , node_list)
        {
            var1->couleur=var1->aux_couleur;
            var1->update();
            scene()->update();
        }
        delay(1);
   }
    DFS1=0;
    }
    else
        return;
}

void GraphWidget::del_node(Node*source_node)
{

    if(!(new_tree1||add_node1||BFS1||DFS1||del_node1||del_all1))
    {
        del_node1=1;

    foreach (Edge*var1, source_node->edgeList)
    {
        scene()->removeItem(var1);
    }
    double opacity=1;
    QSound delete_sound(":/sound/deletesound.wav");
    delete_sound.play();
    for(int i=0;i<30;i++)
    {
       opacity-=0.025;
       source_node->setOpacity(opacity);
       source_node->size+=2;
       source_node->update();
       scene()->update();
       delay(0.05);
    }

    source_node->edgeList.clear();
    if(source_node->parent!=0)
    {
        source_node->parent->children_list.removeOne(source_node);
    }
    scene()->removeItem(source_node);
    node_list.removeOne(source_node);

    dispaly->setText(QString::number(node_list.size()));
    del_node1=0;
    }
    else
        return;
}

void GraphWidget::del_node2(Node*source_node)
{
        if(source_node->parent!=0)
        {
            source_node->parent->children_list.removeOne(source_node);
        }
        scene()->removeItem(source_node);
        node_list.removeOne(source_node);
}

void GraphWidget::del_all()
{
    if(!(new_tree1||add_node1||BFS1||DFS1||del_node1||del_all1))
    {
    del_all1=1;
    QSound delete_sound(":/sound/deletesound.wav");
    if(!node_list.isEmpty())
    {
        foreach (Node*var2, node_list)
        {
            foreach (Edge*var1, var2->edgeList)
            {
               scene()->removeItem(var1);
            }
            var2->edgeList.clear();
        }
        double opacity=1;
       delete_sound.play();
        for(int i=0;i<30;i++)
          {
            opacity-=0.025;
            delay(0.05);
            foreach (Node*var2, node_list)
            {
                var2->setOpacity(opacity);
                var2->size+=2;
                var2->update();
                scene()->update();
            }
            scene()->update();
          }

        foreach (Node*var2, node_list)
        {
           del_node2(var2);
        }

        dispaly->setText(QString::number(node_list.size()));
    }
    del_all1=0;
    }
    else
        return;
}

void GraphWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    foreach (Node *node, node_list)
    {
        node->Forces();
        foreach (Edge *edge, node->edgeList)
           edge->adjust();
    }
}

void GraphWidget::delay(double sec)
{
    QTime dieTime= QTime::currentTime().addMSecs(sec*1000);
    while (QTime::currentTime() < dieTime)
    {
         QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

