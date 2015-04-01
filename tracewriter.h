#ifndef TRACEWRITER_H
#define TRACEWRITER_H
#include<QString>
#include"dataitem.h"
#include <QFile>
#include <QTextStream>

class TraceWriter
{
public:
    TraceWriter(QString dataName, QString genAlgName, QString algName );
    ~TraceWriter();
    void setAlgName(QString algName);
    void setGenAlgName(QString name);
    void setData(QString name);

    void writeTrace();
    void insertionSortWrite();
    void mergeSortWrite();
    bool fileEixsts();  // check if current tracefile exists
private:
    // helper struct
    struct SData{
        int id;
        int size;
    };
    QString fileName;
    QString algName;
    QString genAlgName;
    QString dataName;

    //mergesort helper
    void mergeSort(QTextStream &out, int, int, QMap<int, SData>&, int origSize);
    void merge(QTextStream &out, int start, int mid, int end, QMap<int, SData> &data, int origSize);
    void writeDicLine(QTextStream &out, int startIndex, int endIndex,  QMap<int, SData>& data);

};

#endif // TRACEWRITER_H
