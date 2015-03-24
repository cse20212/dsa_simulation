#include "selectionsort.h"

<<<<<<< HEAD
SelectionSort::SelectionSort(int innerCounter, int outerCounter):Algorithm("SelectionSort", "Sorting")
=======
SelectionSort::SelectionSort(int innerCounter, int outterCounter):Algorithm("SelectionSort", "Sorting")
>>>>>>> 2549beef6a6298db19adede2db1c2b6d994a9b23
{

}

SelectionSort::~SelectionSort()
{

}

void SelectionSort::advanceAlg(){
    //pure virtual; set dataset to the state after next state
    QString name = "Algorithm::name";

    DataSet* set = getDataSet();
    QList<DataItem*>* items = set->getItems();
    //algorithm finished



}

void SelectionSort::back(){
        QString name1 = "Algorithm::name";
}
