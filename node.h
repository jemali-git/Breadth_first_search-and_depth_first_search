#include <QGraphicsItem>
#include <QList>
#include<QtCore>
#include<QPushButton>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QColor>

class Edge;
class GraphWidget;
class QGraphicsSceneMouseEvent;
class Node :public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Node(GraphWidget *graphWidget);
    void addEdge(Edge *edge);

    enum { Type = UserType + 1 };
    int type() const { return Type; }

    void Forces();

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
signals:
    void node_click_right(Node*source_node);
    void node_click_left(Node*source_node);
public slots:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);

public:
    QList<Edge *> edgeList;
    QPointF newPos;
    GraphWidget *graph;
    QColor couleur;
    QColor aux_couleur;
    int size;
    Node*parent;
    QList<Node*> children_list;
};

