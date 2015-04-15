#include "dataset.h"
#include "dataitem.h"
#include "QFile"
#include <QStringList>
#include <QDebug>
#include <QDir>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


DataSet::DataSet(QString genAlgName, QString name, QString algName):YPOS(100)
{
    localDataPath = "/Users/cindywang/simulator/";
    //seed rand
    srand(time(NULL));
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
<<<<<<< HEAD
    dataPath = (QString)localDataPath + "data/" + genAlgName + "/" + name + ".txt";
=======
    //QString dir = "/Users/marykatewilliams/FinalProject/dsa_simulation";
    dataPath = (QString)":/data/" + genAlgName + "/" + name + ".txt";
>>>>>>> 3f91ea98a14925e0ff5a71ca289b5998a0ae150e
}

void DataSet::setAlgName(QString name) {
    this -> algName = name;
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
    if(!dataFile.open(QFile::ReadWrite |
                      QFile::Text))
        {
            qDebug() << " Could not open the file for reading";
            return;
        }
    QString data = dataFile.readAll();
    QStringList dataList = data.split(',');
    itemDic.clear();
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

 void DataSet::generateRand() {
     if (name =="Random") {
         QFile dataFile(dataPath);
         if(!dataFile.open(QFile::ReadWrite|QFile::Truncate|QFile::Text))
             {
                 qDebug() << " Could not open Random data for writing";
                 return;
             }
         QTextStream in(&dataFile);

         int numElem = 8;
         QString dataString = "";
         int randNum = rand() % 50 + 10;
         dataString = QString(dataString + "%1").arg(randNum);
         for (int i = 1; i < numElem; i++) {
             int randNum = rand() % 50 + 10;
             dataString = QString(dataString + ",%1").arg(randNum);
         }
         dataString = dataString + "\n";
         in << dataString;
         dataFile.close();
         setItems();

         // clear up the trace
         // TODO:: need to clear up everything related to this data
        // QString traceFileName = (QString)localDataPath + "trace/" + name + "_" + genAlgName + "_" + algName + ".txt";
        // QFile traceFile(traceFileName);

         QString tracePath = (QString)localDataPath + "trace";
         QDir dir(tracePath);
         QStringList filters;
         filters << name + "*";
         dir.setNameFilters(filters);
         QStringList fileNames = dir.entryList(QDir::NoDotAndDotDot|QDir::Files);    // return file.txt name
         foreach (QString str, fileNames) {
             QString traceFileName = (QString)localDataPath + "trace/" + str;
             QFile traceFile(traceFileName);
             traceFile.remove();
         }

         //traceFile.remove();
     }
 }
