/* a base class for specific algorithms
 *
 */

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <QString>
#include "dataset.h"

class Algorithm: public QObject
{
    Q_OBJECT
public:
    Algorithm(QString name = "sorting", QString genAlgName = "Random");
    ~Algorithm();


    DataSet *getDataSet();
    void setDataSet(DataSet *set);

    QString getCodeFilePath();
    void setCodeFilePath();    // set code file according to general algorithm name and its specific name
    QString getName();
    QString getGenAlgName();
    virtual void resetCounter()=0;  // reset the algorithm counter
private slots:
    virtual void advanceAlg()=0;   // pure virtual; set dataset to the state after next step
    virtual void back()=0;
signals:
    virtual void updateGraphics()=0;
private:
    QString name;
    QString genAlgName; // name of its corresponding general alg
    QString codeFilePath;
    DataSet *mySet;  // dataSet associated with this alg

};

#endif // ALGORITHM_H
