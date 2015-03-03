#include "dataset.h"
#include "dataitem.h"
#include "QFile"
#include <QStringList>
#include <QDebug>
#include <QDir>

DataSet::DataSet(QString genAlgName, QString name)
{
    items = new QList<DataItem*>();
    this->name = name;
    this->genAlgName = genAlgName;
    setDataPath();
    setItems();
}

DataSet::~DataSet()
{
    // not sure how to delete every item
    for (qint8 i = 0; i < items->size(); i++) {
        delete items->at(i);
    }
    delete items;
}

void DataSet::setDataPath(){
    //QString dir = "/Users/cindywang/simulator";
    dataPath = (QString)":/data/" + genAlgName + "/" + name + ".txt";
}

QString DataSet::getDataPath(){
    return dataPath;
}

QString DataSet::geName(){
    return name;
}

QString DataSet::getGenAlgName(){
    return genAlgName;
}

QList<DataItem *>* DataSet::getItems(){
    return items;
}
// read file and set items
void DataSet::setItems(){
    QFile dataFile(dataPath);
    if(!dataFile.open(QFile::ReadOnly |
                      QFile::Text))
        {
            qDebug() << " Could not open the file for reading";
            return;
        }
    QString data = dataFile.readAll();
    QStringList dataList = data.split(',');
    // initialize DataItems based on the list of string numbers
    qDebug() << dataList.size();
    for (int i = 0; i < dataList.size(); i++) {
        DataItem* item = new DataItem(dataList.at(i).toDouble(), 20, 20, 50, i);
        (*items) << item;
    }
}

double DataSet::getSize(){
    return items->size();
}
