#include "edge.h"
#include "node.h"
#include <math.h>
#include <QPainter>

static const double Pi = 3.14;
static double TwoPi = 2.0 * Pi;

Edge::Edge(Node *sourceNode, Node *destNode)
    : arrowSize(10)
{
    source = sourceNode;
    dest = destNode;
    source->addEdge(this);
    dest->addEdge(this);
    update();
}

void Edge::adjust()
{
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = line.length();

    QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
    sourcePoint = line.p1() + edgeOffset;
    destPoint = line.p2() - edgeOffset;
}
QRectF Edge::boundingRect() const
{
   return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),destPoint.y() - sourcePoint.y()));
}
void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;

    QLineF line(sourcePoint, destPoint);
    if (!line.length())
        return;
     painter->drawLine(line);
    // Draw the arrows
    double angle = ::acos(line.dx() / line.length());
    if (line.dy() >= 0)
        angle = TwoPi - angle;

    QPointF destArrowP1 = destPoint + QPointF(sin(angle - Pi / 3) * arrowSize,
                                              cos(angle - Pi / 3) * arrowSize);

    QPointF destArrowP2 = destPoint + QPointF(sin(angle - Pi + Pi / 3) * arrowSize,
                                              cos(angle - Pi + Pi / 3) * arrowSize);

   painter->setBrush(Qt::black);
    painter->setPen(QPen(Qt::NoPen));
    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
}
