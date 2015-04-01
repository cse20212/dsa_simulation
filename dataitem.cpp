#include "dataitem.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

DataItem::DataItem(double size, double width , double sceneOffset ,
                   double scenePosY, int index ):size(size), width(width),
    sceneOffset(sceneOffset), scenePosY(scenePosY), index(index),
    color(100, 125, 255), shapeChoice(1), id(index)
{

    scenePosX = sceneOffset + index * width;
    normalYPos = scenePosY;
    downYPos = scenePosY + 50;

}

QColor DataItem::getColor() const {
    return color;
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

int DataItem::getId(){
    return id;
}

DataItem::~DataItem()
{

}

void DataItem::advance(int step)
{
    if (!step)
        return;

   // setPos(scenePosX, scenePosY);
    update();
}

QRectF DataItem::boundingRect() const
{
    //qreal adjust = 0.5;
    //return QRectF(- 18 - adjust, -22 - adjust, 60 + adjust, 60 + adjust);
    return QRectF( -width/2, -size , width, 2*size);
}

void DataItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //default
    painter->setBrush(color);
    scenePosY = normalYPos;
    // change through flags
    foreach(ItemFlag f, flags) {
        switch(f){
           case pointed:
           {
                QColor c(255, 0, 0);
                painter->setBrush(c);
                break;
          }
          case copyDown:
          {
            scenePosY = downYPos;
            //setPos(scenePosX, scenePosY);
             break;
          }
        }
    }
    setPos(scenePosX, scenePosY);
    painter->drawRect(-width/2, 0 , width , -size);

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

void DataItem::setFlag(ItemFlag f) {
    // add a flag to item
    if (!flags.contains(f)) {
        flags.append(f);
    }
}

void DataItem::resetFlag(ItemFlag f) {
    // remove this flag from item
    if (flags.contains(f)) {
        flags.removeOne(f);
    }
}
