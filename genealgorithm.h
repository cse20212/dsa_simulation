#ifndef GENEALGORITHM_H
#define GENEALGORITHM_H

#include "genealgorithm.h"
#include <QString>
#include <QList>
#include "algorithm.h"
#include "dataset.h"


class GeneAlgorithm
{
public:
    GeneAlgorithm(QString name);
    GeneAlgorithm();
    ~GeneAlgorithm();

    void setAlgList();
    QList<Algorithm*> getAlgList();
    void setDataList();
    QList<DataSet*> getDataList();

private:
    QString name;
    QList<Algorithm*> algList;
    QList<DataSet*> dataList;
};

#endif // GENEALGORITHM_H
