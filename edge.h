

#include <QGraphicsItem>

class Node;

class Edge : public QGraphicsItem
{
public:
    Edge(Node *sourceNode, Node *destNode);
    void adjust();
    enum { Type = UserType + 2 };
    int type() const { return Type; }

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    
public:
    Node *source, *dest;
    QPointF sourcePoint,destPoint;
    qreal arrowSize;
};
