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
    QString getName();
    QList<QString> getAlgList();
    void setDataList();
    QList<DataSet*> getDataList();

private:
    QString name;
    QList<QString> algList;
    QList<DataSet*> dataList;
};

#endif // GENEALGORITHM_H
