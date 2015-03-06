
#ifndef DATAITEM_H
#define DATAITEM_H

#include <QGraphicsItem>

class DataItem : public QGraphicsItem
{
public:
    DataItem(double size = 1, double width = 10, double sceneOffset = 10,
    double scenePosY = 0, int index = 0 );
    ~DataItem();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget) Q_DECL_OVERRIDE;
    void setShapeChoice(qint8 choice);
    double getScenePosX();
    double getScenePosY();
    double getSize();
    int getIndex();
    void setScenePosX(double x);
    void setScenePosY(double y);
    void setIndex(int in);
    void setpointed(int p);

protected:
    void advance(int step) Q_DECL_OVERRIDE;

private:
    double size; //size of the current data
    double width;
    double sceneOffset; //margin between graphics window and first data item
    double scenePosX;
    double scenePosY;
    int index;   //index of item in dataset
    int isPointed;  // indicate if this data item is currently being processed. 1 for yes
    qreal angle;
    qreal speed;
    qreal mouseEyeDirection;
    QColor color;
    int shapeChoice;
};

#endif // DATAITEM_H
