#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include "algorithm.h"

class InsertionSort : public Algorithm
{
    Q_OBJECT
public:
    InsertionSort();
    ~InsertionSort();

private slots:
    void advance();   // pure virtual; set dataset to the state after next step
    void back();

private:

};

#endif // INSERTIONSORT_H
