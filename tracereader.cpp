#include "tracereader.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

TraceReader::TraceReader(QString dataName, QString genAlgName, QString algName): dataName(dataName),
    genAlgName(genAlgName), algName(algName)
{
    localDataPath = "/Users/marykatewilliams/FinalProject/dsa_simulation/";
    fileName = (QString)localDataPath + "trace/" + dataName + "_" + genAlgName + "_" +algName + ".txt";

}

TraceReader::~TraceReader()
{

}

// read line; index is the number of line
QString TraceReader::simpleSortReader(int index, QMap<int, DataItem*>& itemDic) {
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

        //************ modify data
        QString stateString = "Current Position indices in loops: ";
        // set indices first
        if (indexList.size() != itemDic.size()) {
            qDebug() << "index size not correspond!";
            qDebug() << indexList;
        } else {
            for (int i = 0; i < indexList.size(); i++) {
                if (indexList.at(i).toInt() >=0 ) {    // if a valid id
                   DataItem *item = itemDic[indexList.at(i).toInt()];
                   //set position
                    item->setIndex(i);
                   //set pointed flag
                   if (pointedList.contains(indexList.at(i))) {
                      item->setFlag(pointed);

                      stateString = QString(stateString+"%1 ").arg(i);
                   } else {
                      item->resetFlag(pointed);
                   }
                   // set movedown flag
                   if (moveDownList.contains(indexList.at(i))) {
                      item->setFlag(copyDown);
                   } else {
                      item->resetFlag(copyDown);
                   }
                }
            }
        }

        stateString = QString(stateString + "%1").arg("\n");
        return stateString;
    } else {
        qDebug() <<  "Error: reading line";
        return "Error: Lost data source!";
    }

    traceFile.close();
    //qDebug() << "in reader index list " << stateList[0];
    //return stateList;
}

QString TraceReader::recursiveSortReader(int index, QMap<int, DataItem *> &itemDic) {

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
        QStringList indexList = traceList[0].split(",");    // ids listed in position sequence
        QStringList posList = traceList[1].split(",");  // 3 numbers, low, mid, high of positions
        QStringList leftAuxList = traceList[2].split(",");  // id of data in left auxiliary array
        QStringList rightAuxList = traceList[3].split(",");  // id of data in left auxiliary array
        QStringList pointedList = traceList[4].split(",");

        //************ modify data
        QString stateString = "Current Position indices in loops: ";
        // set indices first
        qDebug() << "recursive sort: " << itemDic.keys() << endl;
        for (int i = 0; i < indexList.size(); i++) {
            if (indexList.at(i).size() > 0 && indexList.at(i).toInt() >=0 ) {    // if a valid id
                DataItem *item = itemDic[indexList.at(i).toInt()];
                   //set position
                item->setIndex(i);
                item->resetFlag(pointed);
                item->resetFlag(copyDown);
            }
        }

        // set quxiliary array
        int low = posList[0].toInt();
        int mid = posList[1].toInt();
        int high = posList[2].toInt();
        for (int i = 0; i < leftAuxList.size(); i++) {
            if (leftAuxList.at(i).size() > 0 && leftAuxList.at(i).toInt() >=0 ) {    // if a valid id
                DataItem *item = itemDic[leftAuxList.at(i).toInt()];
                   //set position
                item->setIndex(i + low);    // add on the offset for aux array
                item->setFlag(copyDown);                
            }
        }
        for (int i = 0; i < rightAuxList.size(); i++) {
            if (rightAuxList.at(i).size() > 0 && rightAuxList.at(i).toInt() >=0 ) {    // if a valid id
                DataItem *item = itemDic[rightAuxList.at(i).toInt()];
                   //set position
                item->setIndex(i + mid + 1);    // add on the offset for aux array
                item->setFlag(copyDown);
            }
        }

        // set pointed data
        for (int i = 0; i < pointedList.size(); i++) {
            if (pointedList.at(i).size() > 0 && pointedList.at(i).toInt() >=0 ) {    // if a valid id
                DataItem *item = itemDic[pointedList.at(i).toInt()];
                   //set position
                item->setFlag(pointed);
            }
        }

        stateString = QString(stateString + "%1").arg("\n");
        return stateString;
    } else {
        qDebug() <<  "Error: reading line";
        return "Error: Lost data source!";
    }

    traceFile.close();



}

void TraceReader::setAlgName(QString algName){
    this->algName = algName;
    fileName = (QString)localDataPath + "trace/" + dataName + "_" + genAlgName + "_" +algName + ".txt";
}
