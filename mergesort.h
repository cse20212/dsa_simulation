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
    MergeSort(MergeSort& that);
    MergeSort& operator=(const MergeSort& right);
    ~MergeSort();

    bool inOrder(); // returns true if data is sorted in ascending order
    void resetCounter();    // reset the algorithm counter
    // setters and getters
    void setOrigIsSet(int);
    void setReplaceIndex(int);
    void setCounterOne(int);
    void setCounterTwo(int);
    void setSortedIndex(QList<int>);

    int getOrigIsSet();
    int getReplaceIndex();
    int getCounterOne();
    int getCounterTwo();
    QList<int> getSortedIndex();
private slots:
    void advanceAlg();   // pure virtual; set dataset to the state after next step
    void backAlg();
signals:
    void updateGraphics();
private:
    void copyDataItemArray(QList<DataItem*>* dest, QList<DataItem*>* src, int start, int end);
    void setArrayYPos(QList<DataItem*>* list);
    void markInTemp(DataItem* item);   // mark item as being in a temp array
    void markInArray(DataItem* item);   // mark item as being in the normal array

    int replaceIndex;   // index of object being replaced in the main array
    int counterOne; // counter at tArrayOne
    int counterTwo;
    QList<DataItem*> arrayOne; // required external array to copy
    QList<DataItem*> arrayTwo;


    QList<int> sortedIndex; // list of previous sorted array index

};


#endif // MERGESORT_H
