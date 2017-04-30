#include <QGraphicsView>
#include<QMouseEvent>
#include<QPushButton>
#include<QList>
#include<QLabel>
#include<QMutex>
#include <QSound>
class Node;
class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:

    GraphWidget(QWidget *parent = 0);
  
    void delay(double sec);
    ~GraphWidget();

signals:

public slots:
    void add_node(Node*source_node);
    void del_node(Node*source_node);
    void del_node2(Node*source_node);
    void del_all();
    void new_tree();

    void BFS();
    void DFS();

protected:
    void timerEvent(QTimerEvent *event);



public:
    int timerId;
    Node *centerNode;
    QList<Node*> node_list;
    int index2;
    QList<QColor> table_color;
    QLabel*dispaly;

    int new_tree1,add_node1,BFS1,DFS1,del_node1,del_all1;
    int*test;


};
