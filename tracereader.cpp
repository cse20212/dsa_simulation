#include "tracereader.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

TraceReader::TraceReader(QString dataName, QString genAlgName, QString algName): dataName(dataName),
    genAlgName(genAlgName), algName(algName)
{
    fileName = "/Users/cindywang/simulator/trace/" + dataName + "_" + genAlgName + "_" +
            algName + ".txt";

}

TraceReader::~TraceReader()
{

}

// read line; index is the number of line
QList<QStringList> TraceReader::simpleSortReader(int index) {
    QList<QStringList> stateList;

    QFile traceFile(fileName);
    traceFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&traceFile);
    //qDebug() << fileName;
    QString line;
    int counter = 0;
    while (counter <= index && !in.atEnd()) {
        line = in.readLine();
        counter++;
    }
    //qDebug() << counter;
    if (counter == index + 1) { // successfully read the index line
        qDebug() << line;
        // get data item index string and        
        QStringList traceList = line.split(";");
        QStringList indexList = traceList[0].split(",");
        QStringList pointedList = traceList[1].split(",");
        QStringList moveDownList;

        stateList.append(indexList);
        stateList.append(pointedList);
        if (traceList.size() > 2) {
            moveDownList = traceList[2].split(",");
            stateList.append(moveDownList);
        }
    } else {
        qDebug() <<  "Error: reading line";
    }

    traceFile.close();
    //qDebug() << "in reader index list " << stateList[0];
    return stateList;

}

void TraceReader::setAlgName(QString algName){
    this->algName = algName;
    fileName = "/Users/cindywang/simulator/trace/" + dataName + "_" + genAlgName + "_" +
            algName + ".txt";
}
