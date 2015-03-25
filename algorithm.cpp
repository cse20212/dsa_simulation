/* a base class for specific algorithms
 *
 */

#include "algorithm.h"
#include <QString>
#include <QDir>

Algorithm::Algorithm(QString name, QString genAlgName)
{
    this->name = name;
    this->genAlgName = genAlgName;

    setCodeFilePath();
}

Algorithm::~Algorithm()
{

}

/*
DataSet* Algorithm::getDataSet() {
    return mySet;
}

void Algorithm::setDataSet(DataSet *set){
    mySet = set;
}
*/

// set pseudocode file
QString Algorithm::getCodeFilePath(){
    return codeFilePath;
}

// set code file according to general algorithm name and its specific name
// genAlgName = sorting; name = insertionsort
void Algorithm::setCodeFilePath(){
    QString resourceName = (QString)":/pseudocode/" + genAlgName + "/" + name + ".txt";
    codeFilePath = resourceName;
}

QString Algorithm::getName(){
    //todo: change name into a better format
    //or add a method getFormatedName
    return name;
}

QString Algorithm::getGenAlgName(){
    return genAlgName;
}



