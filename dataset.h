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
    QMap<DataItem*, int> getOrigIndex();
    void resetIndex();  // set index to original index
    void setItems();
    double getSize();
    void removeAllPointed();    // remove all pointed flag of the data items

    void addItems(QList<DataItem*>* list);  // add dataitem to items

private:
    QString name;
    QString genAlgName;
    QString dataPath;   // path to resources
    QList<DataItem*>* items;
    QMap<DataItem*, int> origIndex;
};

#endif // DATASET_H
