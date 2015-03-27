/* a class that defines a set of data items
 */

#ifndef DATASET_H
#define DATASET_H

#include <QString>
#include <QList>
#include "dataitem.h"
#include "tracereader.h"
#include "tracewriter.h"

class DataSet
{
public:
    DataSet(QString genAlgName = "sorting",QString name = "Inverse",  QString algName = "InsertionSort");
    ~DataSet();

    void setDataPath();
    void setAlgName(QString name);
    QString getDataPath();
    QString getName();
    QString getGenAlgName();
    QString getAlgName();
    QList<DataItem *> getItems();

    void setItems();
    double getSize();


    QString go_back();   // read trace file line index to update dataItems
    QString go_forward();
    QString setDataState(QList<QStringList> &list);    // set datastate based on
    void initState(QString algName);   // set the state to initial state

    void checkTraceFile();  //check if trace file exists for this algorithm, if not write the file

private:
    QString name;
    QString genAlgName;
    QString algName;    // name of specific algorithm acting on
    QString dataPath;   // path to resources


    QMap<int, DataItem*> itemDic;   // dictionary of items based on item id

    double YPOS;  // yposition

    TraceReader* reader;
    TraceWriter* writer;
    int currentTraceIndex;

};

#endif // DATASET_H
