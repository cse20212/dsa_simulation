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

void DataSet::addItems(QList<DataItem*>* list){

    foreach (DataItem* item, *list) {
        items->append(item);
    }
}

void DataSet::removeAllPointed(){
    foreach (DataItem* item, *items) {
        item->setpointed(0);
        item->update();
    }
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
        DataItem* item = new DataItem(dataList.at(i).toDouble(), 20, 100, 100, i);
        (*items) << item;
       origIndex[item] = i;
    }
}

double DataSet::getSize(){
    return items->size();
}

 QMap<DataItem*, int> DataSet::getOrigIndex(){
     return origIndex;
 }

 void DataSet::resetIndex(){
     int n = items->size(); // number of items
     DataItem* newItems[n]; //helper array to store the right sequence of data
     foreach (DataItem* item, *items) {
         int index = origIndex[item];
         item->setIndex(index);
         newItems[index] = item;
     }
     items->clear();
     for (int i = 0; i < n; i++) {
         items->append(newItems[i]);
     }
 }


