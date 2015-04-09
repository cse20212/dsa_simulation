#include "dataset.h"
#include "dataitem.h"
#include "QFile"
#include <QStringList>
#include <QDebug>
#include <QDir>


DataSet::DataSet(QString genAlgName, QString name, QString algName):YPOS(100)
{
    reader = new TraceReader(name, genAlgName, algName);
    this->name = name;
    this->genAlgName = genAlgName;
    this->algName = algName;
    setDataPath();
    setItems();

    writer = new TraceWriter(name, genAlgName, algName);
    currentTraceIndex = 0;

    // check if trace file exists
    checkTraceFile();
}

DataSet::~DataSet()
{

    delete reader;
    delete writer;
}

void DataSet::checkTraceFile(){
    if (!writer->fileEixsts()) {
        writer->writeTrace();
        qDebug() << "File not exits!";
    }
}

void DataSet::setDataPath(){
    //QString dir = "/Users/marykatewilliams/FinalProject/dsa_simulation";
    dataPath = (QString)":/data/" + genAlgName + "/" + name + ".txt";
}

void DataSet::setAlgName(QString name) {
    algName = name;
    reader->setAlgName(name);
    writer->setAlgName(name);
}

QString DataSet::getAlgName(){
    return algName;
}

QString DataSet::getDataPath(){
    return dataPath;
}

QString DataSet::getName(){
    return name;
}

QString DataSet::getGenAlgName(){
    return genAlgName;
}

QList<DataItem *> DataSet::getItems(){
    return itemDic.values();
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
        DataItem* item = new DataItem(dataList.at(i).toDouble(), 20, 100, YPOS, i);

       itemDic.insert(item->getId(), item);
    }

    dataFile.close();
}

double DataSet::getSize(){
    return itemDic.size();
}


QString DataSet::go_back() {
    if (currentTraceIndex > 0) {
        currentTraceIndex--;
        QString stateString;
        if (algName == "InsertionSort") {
            stateString = reader->simpleSortReader(currentTraceIndex, itemDic);
        } else {
            stateString = reader->recursiveSortReader(currentTraceIndex, itemDic);
        }

        if (!stateString.contains("Error")) {
            return stateString;
        } else {
            currentTraceIndex++;    //read not success; reset
            qDebug() << "state string is error!";
        }
    } else {
        qDebug() << "Already reach the end!";
        return "Start of algorithm!";
    }

    return NULL;
}

QString DataSet::go_forward() {
        currentTraceIndex++;
        QString stateString;
        if (algName == "InsertionSort") {
            stateString = reader->simpleSortReader(currentTraceIndex, itemDic);
        } else {
            stateString = reader->recursiveSortReader(currentTraceIndex, itemDic);
        }
        if (!stateString.contains("Error")) {
            return stateString;
        } else {
            currentTraceIndex--;    //read not success; reset
            qDebug() << "stateList is null! might have reached the end of algorithm";
            return "End of Algorithm. Please reset to restart simulation.";
        }
        return NULL;
}

void DataSet::initState(QString algName) {
    setAlgName(algName);

    checkTraceFile();   // check if new alg data combination has corresponding trace file
    currentTraceIndex = 0;
    QString stateString;
    if (algName == "InsertionSort" ||  algName == "SelectionSort") {
        stateString = reader->simpleSortReader(currentTraceIndex, itemDic);
    } else if(algName == "MergeSort") {
        stateString = reader->recursiveSortReader(currentTraceIndex, itemDic);
    }

    if (!stateString.contains("Error"))
        //return stateString;
        stateString = "Initialize";
    else
        qDebug() << "stateList is null! might have reached the end of algorithm";
}


/********************
 * not in use currently
 * *********************/
 QString DataSet::setDataState(QList<QStringList> &list){
     QString stateString = "Current Position indices in loops: ";

     int n = list.size();
     QStringList indexList, pointedList, moveDownList;
     if (n >= 2) {
        indexList = list[0];
        pointedList = list[1];
     }
     if (n >= 3) {
         moveDownList = list[2];
     }
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
 }
