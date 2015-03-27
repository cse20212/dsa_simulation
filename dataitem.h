
#ifndef DATAITEM_H
#define DATAITEM_H

#include <QGraphicsItem>
enum ItemFlag {pointed = 1, copyDown = 2};

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

    double getWidth() const;
    QColor getColor() const;
    int getShapeChoice() const;
    void setScenePosX(double x);
    void setScenePosY(double y);
    void setIndex(int in);


    void setFlag(ItemFlag);
    void resetFlag(ItemFlag);

    int getId();

protected:
    void advance(int step) Q_DECL_OVERRIDE;

private:
    double size; //size of the current data
    double width;
    double sceneOffset; //margin between graphics window and first data item
    double scenePosX;
    double scenePosY;

    int id; // number id of the item; original indexed
    int index;   //index of item in dataset

    QColor color;
    int shapeChoice;

    QList<ItemFlag>  flags; // flags for this item

    int normalYPos;
    int downYPos;
};

#endif // DATAITEM_H
