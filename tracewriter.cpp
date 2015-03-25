#include "tracewriter.h"
#include<QFileInfo>
#include<QDebug>
//helper data struct


TraceWriter::TraceWriter(QString dataName, QString genAlgName, QString algName):
    dataName(dataName), algName(algName), genAlgName(genAlgName)
{
    this->fileName = "/Users/cindywang/simulator/trace/" + dataName + "_" + genAlgName + "_" +
            algName + ".txt";
}

TraceWriter::~TraceWriter()
{

}
void TraceWriter::setAlgName(QString algName){
    this->algName = algName;
    this->fileName = "/Users/cindywang/simulator/trace/" + dataName + "_" + genAlgName + "_" +
            algName + ".txt";
}

void TraceWriter::setGenAlgName(QString name){
    this->genAlgName = name;
}

void TraceWriter::setData(QString name){
    this->dataName = name;
}

void TraceWriter::writeTrace(){
    if (!fileEixsts()) {
        if (algName == "InsertionSort") {
            insertionSortWrite();
        }
    }
}

void TraceWriter::insertionSortWrite(){
    QMap<int, SData> dataDic; // dictionary of data<position, data>
    //first get data from resource file and put them in a map
    QString dataPath = (QString)":/data/" + genAlgName + "/" + dataName + ".txt";
    QFile dataFile(dataPath);
    if(!dataFile.open(QFile::ReadOnly |
                      QFile::Text))
        {
            qDebug() << "TraceWriter: Could not open the file for reading";
            return;
        }
    QString data = dataFile.readAll();
    QStringList dataList = data.split(',');
    // initialize DataItems based on the list of string numbers
    qDebug() << dataList.size();
    for (int i = 0; i < dataList.size(); i++) {
        SData d = {i, dataList.at(i).toInt()};
       dataDic.insert(i, d);
    }

    // open the file for writing
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    /******************
     * algorithm logic
     * *******************/

    // write the initial state
    // write a line to out
    QString inputString = "";
    for(int index = 0; index < dataDic.keys().size(); index++) {
        inputString =  QString(inputString+"%1").arg(dataDic[index].id);
        if (index != dataDic.keys().size()-1)
            inputString = (QString)inputString + ",";
    }
    inputString = QString(inputString + ";;\n");
    //qDebug() << dataDic.keys()[k];
    out << inputString;


    int n = dataDic.size();

    for (int i = 1; i < n; i++) {
        for (int k = i; k >=1; k--) {
            SData data1 = dataDic.values()[k-1];
            SData data2 = dataDic.values()[k];
            if (data2.size < data1.size) {
                dataDic[k-1] = data2;
                dataDic[k] = data1;
            }
            // write a line to out
            QString inputString = "";
            for(int index = 0; index < dataDic.keys().size(); index++) {
                inputString =  QString(inputString+"%1").arg(dataDic[index].id);
                if (index != dataDic.keys().size()-1)
                    inputString = (QString)inputString + ",";
            }
            inputString = QString(inputString + ";%1,%2;\n").arg(dataDic[i].id).arg(dataDic[k].id);
            //qDebug() << dataDic.keys()[k];
            out << inputString;
        }
    }

    // optional, as QFile destructor will already do it:
    file.close();
}

bool TraceWriter::fileEixsts(){
    QFileInfo checkFile(fileName);
    if (checkFile.exists() && checkFile.isFile()) {
            return true;
        } else {
            //qDebug()<<fileName;
            return false;

        }
}
