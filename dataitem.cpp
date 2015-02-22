#include "dataitem.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

DataItem::DataItem(double size):size(size), angle(0), speed(0), mouseEyeDirection(0),
    color(100, 125, 255), shapeChoice(1)
{

}

DataItem::~DataItem()
{

}

void DataItem::advance(int step)
{
    if (!step)
        return;

    setPos(mapToParent(0, 1));
}

QRectF DataItem::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(- 18 - adjust, -22 - adjust, 36 + adjust, 60 + adjust);
}

void DataItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Body
    painter->setBrush(color);
    painter->drawRect(-5, 0, 10, -size);
    /*
    // Eyes
    painter->setBrush(Qt::white);
    painter->drawEllipse(-10, -17, 8, 8);
    painter->drawEllipse(2, -17, 8, 8);

    // Nose
    painter->setBrush(Qt::black);
    painter->drawEllipse(QRectF(-2, -22, 4, 4));

    // Pupils
    painter->drawEllipse(QRectF(-8.0 + mouseEyeDirection, -17, 4, 4));
    painter->drawEllipse(QRectF(4.0 + mouseEyeDirection, -17, 4, 4));

    // Ears
    painter->setBrush(scene()->collidingItems(this).isEmpty() ? Qt::darkYellow : Qt::red);
    painter->drawEllipse(-17, -12, 16, 16);
    painter->drawEllipse(1, -12, 16, 16);

    // Tail
    QPainterPath path(QPointF(0, 20));
    path.cubicTo(-5, 22, -5, 22, 0, 25);
    path.cubicTo(5, 27, 5, 32, 0, 30);
    path.cubicTo(-5, 32, -5, 42, 0, 35);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(path);
    */
}

// used for collision detection...
QPainterPath DataItem::shape() const
{
    QPainterPath path;
    path.addRect(-10, -20, 20, 40);
    return path;
}



