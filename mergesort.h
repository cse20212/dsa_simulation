#ifndef MERGESORT_H
#define MERGESORT_H


#include "algorithm.h"
#include "dataitem.h"
#include <QList>

class MergeSort : public Algorithm
{
    Q_OBJECT
public:
    MergeSort(int counterOne = 0, int counterTwo = 0);
    ~MergeSort();
    bool inOrder(); // returns true if data is sorted in ascending order
    void resetCounter();    // reset the algorithm counter

private slots:
    void advanceAlg();   // pure virtual; set dataset to the state after next step
    void backAlg();
signals:
    void updateGraphics();
private:
    void copyDataItemArray(QList<DataItem*>* dest, QList<DataItem*>* src, int start, int end);
    void setArrayYPos(QList<DataItem*>* list);
    int innerCounter;
    int outterCounter;

    int replaceIndex;   // index of object being replaced in the main array
    int counterOne; // counter at tArrayOne
    int counterTwo;
    QList<int> sortedIndex; // list of previous sorted array index
    QList<DataItem*>* tArrayOne; // required external array to copy
    QList<DataItem*>* tArrayTwo;
    QList<DataItem*> origData; // original list of dataset
};


#endif // MERGESORT_H
