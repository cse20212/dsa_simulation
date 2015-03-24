#include "selectionsort.h"

SelectionSort::SelectionSort():Algorithm("SelectionSort", "Sorting")
{

}

SelectionSort::~SelectionSort()
{

}

void SelectionSort::advance(){
    //pure virtual; set dataset to the state after next state
    QString name = "Algorithm::name";

    DataSet* set = getDataSet();
    QList<DataItem*>* items = set->getItems();
    //algorithm finished



}

void SelectionSort::back(){
        QString name1 = "Algorithm::name";
}
