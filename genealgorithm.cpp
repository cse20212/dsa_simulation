#include "genealgorithm.h"
#include <QString>
#include <QDir>
#include "algorithm.h"
<<<<<<< HEAD
#include "insertionsort.h"
#include "selectionsort.h"
#include "mergesort.h"
=======
>>>>>>> mergesortBranch
#include "dataset.h"

GeneAlgorithm::GeneAlgorithm(QString name):name(name)
{
    setDataList();
    setAlgList();
}
GeneAlgorithm::GeneAlgorithm(){
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
<<<<<<< HEAD
           InsertionSort *insertionSort = new InsertionSort();
           algList.append(insertionSort);
           MergeSort *mergeSort = new MergeSort();
           algList.append(mergeSort);
           SelectionSort *selectionSort = new SelectionSort();
           algList.append(selectionSort);
=======
           //InsertionSort *insertionSort = new InsertionSort();
           algList.append("InsertionSort");
>>>>>>> mergesortBranch

    }
}

QList<QString> GeneAlgorithm::getAlgList(){
    return algList;
}
// search through the directory for list
void GeneAlgorithm::setDataList(){
    /*
    QString dirName = "/Users/cindywang/simulator/";
    QString filePath = dirName + "data/" + name ;
    */
    QString filePath = (QString)":/" + "data/" + name;
    QDir dir(filePath);
    QStringList fileNames = dir.entryList(QDir::NoDotAndDotDot|QDir::Files);    // return file.txt name
    foreach (QString str, fileNames) {
        str = (str.split(".") ).at(0);  // remove .txt
        DataSet *mySet = new DataSet(name, str);
        dataList.append(mySet);
    }
}

QList<DataSet*> GeneAlgorithm::getDataList(){
    return dataList;
}

