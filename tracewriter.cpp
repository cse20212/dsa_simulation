#include "tracewriter.h"
#include<QFileInfo>
#include<QDebug>
//helper data struct


TraceWriter::TraceWriter(QString dataName, QString genAlgName, QString algName):
    dataName(dataName), algName(algName), genAlgName(genAlgName)
{
    localDataPath = "/Users/cindywang/simulator/";
    this->fileName = (QString)localDataPath + "trace/" + dataName + "_" + genAlgName + "_" + algName + ".txt";
}

TraceWriter::~TraceWriter()
{

}
void TraceWriter::setAlgName(QString algName){
    this->algName = algName;
    this->fileName = (QString)localDataPath + "trace/" + dataName + "_" + genAlgName + "_" +algName + ".txt";
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
        } else if (algName == "MergeSort"){
            mergeSortWrite();
        } else if (algName == "SelectionSort"){
            selectionSortWrite();
        }
    }
}

void TraceWriter::insertionSortWrite(){
    QMap<int, SData> dataDic; // dictionary of data<position, data>
    //first get data from resource file and put them in a map
    QString dataPath = (QString)localDataPath + "data/" + genAlgName + "/" + dataName + ".txt";
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


void TraceWriter::selectionSortWrite(){
    QMap<int, SData> dataDic; // dictionary of data<position, data>
    //first get data from resource file and put them in a map
    QString dataPath = (QString)localDataPath + "data/" + genAlgName + "/" + dataName + ".txt";
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
    int minIndex;
    int minVal;

    for (int i = 0; i < n-1; i++) {
        minIndex=i;
        minVal = dataDic[i].size;
        for (int k = i+1; k<n; k++) {
            SData data2 = dataDic.values()[k];
            if (data2.size < minVal) {
                minIndex=k;
                minVal = data2.size;
            }
            // write a line to out
             QString inputString = "";
            for(int index = 0; index < dataDic.keys().size(); index++) {
                 inputString =  QString(inputString+"%1").arg(dataDic[index].id);
                 if (index != dataDic.keys().size()-1)
                 inputString = (QString)inputString + ",";
            }
            inputString = QString(inputString + ";%1,%2,%3;\n").arg(dataDic[i].id).arg(dataDic[k].id).arg(dataDic[minIndex].id);
             //qDebug() << dataDic.keys()[k];
             out << inputString;
        }
        SData dataMin = dataDic.values()[minIndex];
        SData data1 = dataDic.values()[i];
        if(minIndex!=i){
            dataDic[i] = dataMin;
            dataDic[minIndex] = data1;
        }
        // write a line to out
        QString inputString = "";
        for(int index = 0; index < dataDic.keys().size(); index++) {
             inputString =  QString(inputString+"%1").arg(dataDic[index].id);
             if (index != dataDic.keys().size()-1)
             inputString = (QString)inputString + ",";
        }
       inputString = QString(inputString + ";%1,%2;\n").arg(dataDic[i].id).arg(dataDic[minIndex].id);
       //qDebug() << dataDic.keys()[k];
       out << inputString;
     }


    // optional, as QFile destructor will already do it:
    file.close();
}


void TraceWriter::mergeSortWrite(){
    QMap<int, SData> dataDic; // dictionary of data<position, data>
    //first get data from resource file and put them in a map
    QString dataPath = (QString)localDataPath + "data/" + genAlgName + "/" + dataName + ".txt";
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
    inputString = QString(inputString + ";0,0,0;;;;\n");
    //qDebug() << dataDic.keys()[k];
    out << inputString;


    int n = dataDic.size();
    mergeSort(out, 0, n-1, dataDic, n);

    // optional, as QFile destructor will already do it:
    file.close();
}
void TraceWriter::mergeSort(QTextStream &out, int start, int end, QMap<int, SData> &data, int origSize) {
    if (start >= end) return;
    int mid = start + (end - start)/2;
    mergeSort(out, start, mid, data, origSize);
    mergeSort(out, mid+1, end, data, origSize);
    merge(out, start, mid, end, data, origSize);
}

void TraceWriter::merge(QTextStream &out, int start, int mid, int end, QMap<int, SData> &data,int origSize) {
    int left = start;
    int right = mid+1;
    int current = start;

    int dataSize = origSize;
    //copy data into aux arrays
    QMap<int, SData> leftArray;
    for (int i = left; i <= mid; i++) {
        leftArray.insert(i, data[i]);
        data.remove(i);
    }
    QMap<int, SData> rightArray;
    for (int i = right; i <= end; i++) {
        rightArray.insert(i, data[i]);
        data.remove(i);
    }
    int leftSize = leftArray.size();
    int rightSize = rightArray.size();

    // write initial state to out
    writeDicLine(out, 0, dataSize-1, data);

    QString inputString = QString("%1,%2,%3;").arg(start).arg(mid).arg(end);   // start, mid, end
    out << inputString;

    writeDicLine(out, left, mid, leftArray);
    writeDicLine(out, right, end, rightArray);

    out << QString("%1,%2;").arg(left).arg(right);  // pointed, pointed;
    out << "\n";

    while(left <= mid && right <= end) {
        SData data1 = leftArray[left];
        SData data2 = rightArray[right];
        if (data2.size < data1.size) {
           // if (!data.contains(current))
                data.insert(current, data2);
           // else
           //     data[current] = data2;
            rightArray.remove(right);
            right++;
        } else {
           // if (!data.contains(current))
                data.insert(current, data1);
           // else
           //     data[current] = data1;
            leftArray.remove(left);
            left++;
        }        
        current++;

        /******
         * write data; might put these code in a function
         * *****/
        writeDicLine(out, 0, dataSize-1, data);

        QString inputString = QString("%1,%2,%3;").arg(start).arg(mid).arg(end);   // start, mid, end
        out << inputString;

        writeDicLine(out, left, mid, leftArray);
        writeDicLine(out, right, end, rightArray);

        //out << QString("%1,%2;").arg(left).arg(right);  // pointed, pointed;
        out << QString(";");  // pointed, pointed;
        out << "\n";
    }

    while (left <= mid) {
      //  if (!data.contains(current))
            data.insert(current, leftArray[left]);
      //  else
      //      data[current] = leftArray[left];
        leftArray.remove(left);
        left++;
        current++;
        /******
         * write data; might put these code in a function
         * *****/
        writeDicLine(out, 0, dataSize-1, data);

        QString inputString = QString("%1,%2,%3;").arg(start).arg(mid).arg(end);   // start, mid, end
        out << inputString;

        writeDicLine(out, left, mid, leftArray);
        writeDicLine(out, right, end, rightArray);

        //out << QString("%1,%2;").arg(left).arg(right);  // pointed, pointed;
        out << QString(";");  // pointed, pointed;
        out << "\n";
    }
    while (right <= end) {
     //   if (!data.contains(current))
            data.insert(current, rightArray[right]);
     //   else
     //       data[current] = rightArray[right];
        rightArray.remove(right);
        right++;
        current++;
        /******
         * write data; might put these code in a function
         * *****/
        writeDicLine(out, 0, dataSize-1, data);

        QString inputString = QString("%1,%2,%3;").arg(start).arg(mid).arg(end);   // start, mid, end
        out << inputString;

        writeDicLine(out, left, mid, leftArray);
        writeDicLine(out, right, end, rightArray);

        //out << QString("%1,%2;").arg(left).arg(right);  // pointed, pointed;
        out << QString(";");  // pointed, pointed;
        out << "\n";
    }
}

// write dic as a line in for , , , ; with data, or nothing if data missing
void TraceWriter::writeDicLine(QTextStream &out, int startIndex, int endIndex,  QMap<int, SData>& data) {
    QString inputString = "";
    for(int index = startIndex; index <= endIndex; index++) {
        if (data.contains(index)) {
            qDebug() << data[index].id;
            inputString =  QString(inputString+"%1").arg(data[index].id);
        }
        if (index != endIndex)
            inputString = (QString)inputString + ",";
    }
    out << inputString + ";";
}

bool TraceWriter::fileEixsts(){
    QFileInfo checkFile(fileName);
    if (checkFile.exists() && checkFile.isFile() && checkFile.size() > 0) {
            return true;
        } else {
            //qDebug()<<fileName;
            return false;

        }
}
