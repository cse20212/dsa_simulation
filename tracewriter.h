#ifndef TRACEWRITER_H
#define TRACEWRITER_H
#include<QString>
#include"dataitem.h"

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
    bool fileEixsts();  // check if current tracefile exists
private:
    QString fileName;
    QString algName;
    QString genAlgName;
    QString dataName;
    // helper struct
    struct SData{
        int id;
        int size;
    };
};

#endif // TRACEWRITER_H
