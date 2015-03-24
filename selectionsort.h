#ifndef SELECTIONSORT
#define SELECTIONSORT

#include "algorithm.h"

class SelectionSort: public Algorithm
{
        Q_OBJECT
public:
    SelectionSort(int innerCounter =1, int outterCounter=0);
    ~SelectionSort();
    bool inOrder();
    void resetCounter();

private slots:
    void advanceAlg();
    void backAlg();
signals:
    void updateGraphics();
private:
    int innerCounter;
    int outterCounter;
    int Min;
    int iMin;

};

#endif // SELECTIONSORT

