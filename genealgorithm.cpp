#include "genealgorithm.h"
#include <QString>
#include <QDir>
#include "algorithm.h"

#include "dataset.h"

GeneAlgorithm::GeneAlgorithm(QString name):name(name)
{
    localDataPath = "/Users/cindywang/simulator/";
    setDataList();
    setAlgList();
}
GeneAlgorithm::GeneAlgorithm(){
    localDataPath = "/Users/cindywang/simulator/";
    name = "sorting";
    setDataList();
    setAlgList();
}

GeneAlgorithm::~GeneAlgorithm()
{

}

// search through the directory for list
void GeneAlgorithm::setAlgList(){
    if (name == "sorting"){
        // initialize soring algorithm classes
           algList.append("InsertionSort");
           algList.append("MergeSort");
           algList.append("SelectionSort");
    }
}

QList<QString> GeneAlgorithm::getAlgList(){
    return algList;
}
// search through the directory for list
void GeneAlgorithm::setDataList(){
    QString filePath = (QString)localDataPath + "data/" + name;
    QDir dir(filePath);
    QStringList fileNames = dir.entryList(QDir::NoDotAndDotDot|QDir::Files);    // return file.txt name
    foreach (QString str, fileNames) {
        str = (str.split(".") ).at(0);  // remove .txt
        DataSet *mySet = new DataSet(name, str, "InsertionSort");
        dataList.append(mySet);
    }
}

QList<DataSet*> GeneAlgorithm::getDataList(){
    return dataList;
}

QString GeneAlgorithm::getName(){
        return name;
}

