
#ifndef DATAITEM_H
#define DATAITEM_H

#include <QGraphicsItem>

class DataItem : public QGraphicsItem
{
public:
    DataItem(double size = 1);
    ~DataItem();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget) Q_DECL_OVERRIDE;
    void setShapeChoice(qint8 choice);

protected:
    void advance(int step) Q_DECL_OVERRIDE;

private:
    double size; //size of the current data
    qreal angle;
    qreal speed;
    qreal mouseEyeDirection;
    QColor color;
    int shapeChoice;
};

#endif // DATAITEM_H
