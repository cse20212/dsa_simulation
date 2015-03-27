#ifndef TRACEREADER_H
#define TRACEREADER_H

#include <QString>
#include "dataitem.h"

// a class to read data trace files and modify data items accordingly
class TraceReader
{
public:
    TraceReader(QString dataName, QString genAlgName, QString algName);
    ~TraceReader();

    void setAlgName(QString algName);
    QString simpleSortReader(int index, QMap<int, DataItem *> &itemDic); // read the trace file for simple sorting algorithm
                                                    // and reset the dataitems in set
    QString recursiveSortReader(int index, QMap<int, DataItem *> &itemDic);
private:
    QString dataName;
    QString genAlgName;
    QString algName;
    QString fileName;

};

#endif // TRACEREADER_H
