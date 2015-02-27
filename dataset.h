/* a class that defines a set of data items
 */

#ifndef DATASET_H
#define DATASET_H

#include <QString>
#include <QList>
#include "dataitem.h"

class DataSet
{
public:
    DataSet(QString name = "inverse", QString genAlgName = "sorting");
    ~DataSet();

    void setDataPath();
    QString getDataPath();
    QString geName();
    QString getGenAlgName();
    QList<DataItem *> *getItems();
    void setItems();
    double getSize();

private:
    QString name;
    QString genAlgName;
    QString dataPath;   // path to resources
    QList<DataItem*>* items;
};

#endif // DATASET_H
