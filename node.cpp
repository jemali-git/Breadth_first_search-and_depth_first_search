#include "edge.h"
#include "node.h"
#include "graphwidget.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QColor>
#include<QLabel>

Node::Node(GraphWidget *graphWidget)
{
    graph=graphWidget;
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    this->setToolTip("double clique = droite:ajouter gauche:supprimer");
    size=20;
}
void Node::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event)
{
    if(event->button()==Qt::RightButton)
    {
     emit node_click_right(this);
    }
    else if(event->button()==Qt::LeftButton)
    {
        emit node_click_left(this);
    }
}

void Node::addEdge(Edge *edge)
{
    edgeList << edge;
}


void Node::Forces()
{
    if ( scene()->mouseGrabberItem() == this) {
        newPos = pos();
        return;
      }
    double xvel = 0;

    double yvel = 0;
    foreach (QGraphicsItem *item, scene()->items())
    {
        Node *node = qgraphicsitem_cast<Node *>(item);
        if (!node)
            continue;

        QPointF vec = mapToItem(node, 0, 0);
        qreal dx = vec.x();
        qreal dy = vec.y();
        double l =  (dx * dx + dy * dy);
        if (l > 0) {
            xvel += (dx*50 ) / l;
            yvel += (dy*50) / l;
        }
    }
    double weight = (edgeList.size() +1) * 10;
    foreach (Edge *edge, edgeList) {
        QPointF vec;
        if (edge->source == this)
            vec = mapToItem(edge->dest, 0, 0);
        else
            vec = mapToItem(edge->source, 0, 0);
        xvel -= vec.x() / weight;
        yvel -= vec.y() / weight;
    }
    if (qAbs(xvel) < 0.1 && qAbs(yvel) < 0.1)
        xvel = yvel = 0;
    QRectF sceneRect = scene()->sceneRect();
    newPos = pos() + QPointF(xvel, yvel);
   newPos.setX(qMin(qMax(newPos.x(), sceneRect.left() + size/2), sceneRect.right() - size/2));
   newPos.setY(qMin(qMax(newPos.y(), sceneRect.top() + size/2), sceneRect.bottom() - size/2));
   setPos(newPos);
}

QRectF Node::boundingRect() const
{

    return QRectF( -11, -11, 22, 22);
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    Q_UNUSED(option);
    QRadialGradient gradient(0, 0, 10);

     gradient.setColorAt(1, couleur.light(120));

    painter->setBrush(gradient);

    painter->setPen(QPen(Qt::NoPen));
    painter->drawEllipse(-10, -10, size, size);
}

