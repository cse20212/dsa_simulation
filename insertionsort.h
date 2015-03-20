#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include "algorithm.h"

class InsertionSort : public Algorithm
{
    Q_OBJECT
public:
    InsertionSort(int innerCounter = 1, int outterCounter = 1);
    ~InsertionSort();
    bool inOrder(); // returns true if data is sorted in ascending order
    void resetCounter();    // reset the algorithm counter

private slots:
    void advanceAlg();   // pure virtual; set dataset to the state after next step
    void backAlg();
signals:
    void updateGraphics();
private:
    int innerCounter;
    int outterCounter;
};

#endif // INSERTIONSORT_H
