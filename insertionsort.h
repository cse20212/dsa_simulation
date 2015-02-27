#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include "algorithm.h"

class InsertionSort : public Algorithm
{
    Q_OBJECT
public:
    InsertionSort(int innerCounter = 1, int outterCounter = 1);
    ~InsertionSort();

private slots:
    void advanceAlg();   // pure virtual; set dataset to the state after next step
    void back();
signals:
    void updateGraphics();
private:
    int innerCounter;
    int outterCounter;
};

#endif // INSERTIONSORT_H
