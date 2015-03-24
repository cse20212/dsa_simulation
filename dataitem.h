
#ifndef DATAITEM_H
#define DATAITEM_H

#include <QGraphicsItem>

class DataItem : public QGraphicsItem
{
public:
    DataItem(double size = 1, double width = 10, double sceneOffset = 10,
    double scenePosY = 0, int index = 0 );
    /*
    DataItem(const DataItem* that);
    DataItem& operator=(const DataItem &right);
    */
    ~DataItem();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget) Q_DECL_OVERRIDE;
    void setShapeChoice(qint8 choice);
    double getScenePosX() const;
    double getScenePosY() const;
    double getSize() const;
    int getIndex() const;
    double getSceneOffset() const;
    int getIsPointed() const;
    double getWidth() const;
    QColor getColor() const;
    int getShapeChoice() const;
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

    QColor color;
    int shapeChoice;
};

#endif // DATAITEM_H
