#include "dataitem.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

DataItem::DataItem(double size, double width , double sceneOffset ,
                   double scenePosY, int index ):size(size), width(width),
    sceneOffset(sceneOffset), scenePosY(scenePosY), index(index),
    color(100, 125, 255), shapeChoice(1)
{
    isPointed = 0;  // initially the data is not pointed
    scenePosX = sceneOffset + index * width;
}

DataItem::DataItem(const DataItem* that) {
    size = that->getSize(); //size of the current data
    width = that->getWidth();
    sceneOffset = that->getSceneOffset(); //margin between graphics window and first data item
    scenePosX = that->getScenePosX();
    scenePosY = that->getScenePosY();
    index = that->getIndex();   //index of item in dataset
    isPointed = that->getIsPointed();  // indicate if this data item is currently being processed. 1 for yes

    color = that->getColor();
    shapeChoice = that->getShapeChoice();
}

DataItem& DataItem::operator=(const DataItem &that){
    if (this == &that) {
        return *this;
    } else {
        size = that.getSize(); //size of the current data
        width = that.getWidth();
        sceneOffset = that.getSceneOffset(); //margin between graphics window and first data item
        scenePosX = that.getScenePosX();
        scenePosY = that.getScenePosY();
        index = that.getIndex();   //index of item in dataset
        isPointed = that.getIsPointed();  // indicate if this data item is currently being processed. 1 for yes

        color = that.getColor();
        shapeChoice = that.getShapeChoice();
        return *this;
    }
}

QColor DataItem::getColor() const {
    return color;
}
int DataItem::getIsPointed() const {
    return isPointed;
}
double DataItem::getSceneOffset() const{
    return sceneOffset;
}
double DataItem::getWidth() const {
    return width;
}
int DataItem::getShapeChoice() const {
    return shapeChoice;
}

DataItem::~DataItem()
{

}

void DataItem::advance(int step)
{
    if (!step)
        return;

    setPos(scenePosX, scenePosY);
}

QRectF DataItem::boundingRect() const
{
    //qreal adjust = 0.5;
    //return QRectF(- 18 - adjust, -22 - adjust, 60 + adjust, 60 + adjust);
    return QRectF( -width/2, -size , width, 2*size);
}

void DataItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Body
    painter->setBrush(color);
    painter->drawRect(-width/2, 0 , width , -size);
    if (isPointed) {
        QColor c(255, 0, 0);
        painter->setBrush(c);
        painter->drawRect(-width/2, 0 , width , -size);
    }

}
// p is 1 indicates data is currently being processed, 0 otherwise
void DataItem::setpointed(int p) {
    isPointed  = p;
}

// used for collision detection...
QPainterPath DataItem::shape() const
{
    QPainterPath path;
    path.addRect(-10, -20, 20, 40);
    return path;
}


double DataItem::getScenePosX() const{
    return scenePosX;
}

double DataItem::getScenePosY() const{
    return scenePosY;
}

void DataItem::setScenePosX(double x){
    scenePosX = x;
}

void DataItem::setScenePosY(double y){
    scenePosY = y;
}

double DataItem::getSize() const {
    return size;
}

int DataItem::getIndex() const {
    return index;
}

void DataItem::setIndex(int in) {
    index = in;
    scenePosX = index*width + sceneOffset;
}
