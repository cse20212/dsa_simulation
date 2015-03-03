#ifndef SELECTIONSORT
#define SELECTIONSORT

#include "algorithm.h"

class SelectionSort: public Algorithm
{
        Q_OBJECT
public:
    SelectionSort(int innerCounter =1, int outterCounter=1);
    ~SelectionSort();

private slots:
    void advanceAlg();
    void back();
signals:
    void updateGraphics();
private:

};

#endif // SELECTIONSORT

